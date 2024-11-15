#include "SHA256.cpp" // NOLINT
#include "base64.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "tools/SHA256.h"
#include "zstd.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

auto stringToLower(std::string str) -> std::string
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

	return str;
}

void compressFile(ZSTD_CCtx* cctx, const fs::path& filePath, std::ofstream& archive,
				  size_t chunkSize = 16384)
{
	// open up file for compression
	std::ifstream input(filePath, std::ios::binary);
	std::stringstream output;

	if (!input.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << "\n";
		return;
	}

	// for storing the file i presume
	std::vector<char> inputBuffer(chunkSize);

	// compressed output i guess
	std::vector<char> compressedBuffer(ZSTD_compressBound(chunkSize));

	// append sizeof(filePath) so we know how much to read
	// size is converted to char due to simplicity and because of Windows limits
	// even though Linux is the target platform

	archive << std::hex << static_cast<uint8_t>(filePath.string().size());

	// append actual path, exactly one byte after size (hopefully)
	archive << filePath.string();

	// actual output buffer
	ZSTD_outBuffer zstdOut{compressedBuffer.data(), compressedBuffer.size(), 0};

	// actual input buffer
	ZSTD_inBuffer zstdIn{inputBuffer.data(), 0, 0};

	// actual compression
	// while file is not over
	while (input.read(inputBuffer.data(), static_cast<std::streamsize>(chunkSize)) ||
		   input.gcount() > 0)
	{
		// write input to input buffer
		zstdIn.src = inputBuffer.data();
		zstdIn.size = input.gcount();
		zstdIn.pos = 0;

		// while position valid
		while (zstdIn.pos < zstdIn.size)
		{
			// actual compression
			zstdOut.pos = 0;
			ZSTD_compressStream(cctx, &zstdOut, &zstdIn);

			// append compressed file
			output.write(compressedBuffer.data(),
						 static_cast<std::streamsize>(zstdOut.pos));
		}
	}

	zstdOut.pos = 0;
	size_t remainingToFlush;
	do
	{
		remainingToFlush = ZSTD_endStream(cctx, &zstdOut);
		output.write(compressedBuffer.data(), static_cast<std::streamsize>(zstdOut.pos));
	} while (remainingToFlush != 0);

	// compressed file size
	uint32_t size = output.str().size();

	// append file size, uint32_t chosen because anything over than 4GB
	// just means atp compression wont even work without making a zipbomb lol
	archive.write(reinterpret_cast<const char*>(&size), sizeof(size));

	archive << output.rdbuf();

	input.close();
}

namespace fs = std::filesystem;

auto main(int argc, const char** argv) -> int
{
	if (!std::filesystem::exists("assets"))
	{
		std::cerr << "\"assets\" folder not found, creating...\n";
		std::filesystem::create_directory("assets");
	}

	if (!std::filesystem::exists("project.json"))
	{
		std::cerr << "\"project.json\" file not found, creating...\n";

		rapidjson::Document projectDoc;
		projectDoc.SetObject();

		rapidjson::Value projectVal;
		projectVal.SetObject();
		projectVal.AddMember("name", "Application", projectDoc.GetAllocator());
		projectVal.AddMember("author", "Espresso", projectDoc.GetAllocator());
		projectVal.AddMember("version", "1.0.0", projectDoc.GetAllocator());
		projectVal.AddMember("id", "com.espresso.app", projectDoc.GetAllocator());

		projectDoc.AddMember("project", projectVal, projectDoc.GetAllocator());

		rapidjson::StringBuffer s;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);

		projectDoc.Accept(writer);

		std::ofstream projectFile("project.json");
		projectFile << s.GetString();
		projectFile.close();
	}

	std::string project;
	std::string id;

	{
		std::stringstream projectSS;
		std::ifstream projectFile("project.json");
		projectSS << projectFile.rdbuf();

		SHA256 sha;
		sha.update(projectSS.str());

		project = SHA256::toString(sha.digest()) + projectSS.str();

		rapidjson::Document doc1;
		doc1.Parse(projectSS.str().c_str());

		if (doc1["project"].HasMember("id"))
		{
			id = doc1["project"]["id"].GetString();
		}
		else
		{
			std::cerr << "\"id\" field not found in project.json file!\n";
			id = "com." + stringToLower(doc1["project"]["author"].GetString()) + "." +
				 stringToLower(doc1["project"]["name"].GetString());
		}
	}

	project = base64::to_base64(project);

	// this isnt needed. just for the sake of it
	// things look way more sophisticated when they use binary instead of simple json
	for (char& c : project)
	{
		c = static_cast<char>(static_cast<unsigned char>(c) << 1);
	}

	std::ofstream projectFile("project");
	projectFile << project;
	projectFile.close();

	// this is a mess. im sorry
	// initialize everything for zstd
	std::ofstream archive("assets.pak", std::ios::binary);

	std::filesystem::current_path("assets");

	ZSTD_CCtx* cctx = ZSTD_createCCtx();

	ZSTD_CCtx_setParameter(cctx, ZSTD_cParameter::ZSTD_c_strategy, 9);
	ZSTD_CCtx_setParameter(cctx, ZSTD_c_windowLog, 18);

	for (const auto& entry : fs::recursive_directory_iterator("."))
	{
		if (entry.is_regular_file())
		{
			compressFile(cctx, fs::relative(entry.path(), "."), archive);
		}
	}

	// cleanup
	ZSTD_freeCCtx(cctx);
	archive.close();

	return 0;
}