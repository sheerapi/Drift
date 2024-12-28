#include "components/Text.h"
#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "styles/RenderingStyles.h"
#include "styles/Style.h"
#include "styles/TypographyStyles.h"
#include "utils/Color.h"

using namespace Drift;
using namespace Drift::Styling;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto* root = window->GetCurrentActivity()
					 ->AttachRoot(std::make_shared<Element>())
					 ->FlexDirection(Direction::Column)
					 ->Gap(10)
					 ->Padding(10)
					 ->AddStyle<BackgroundColor>(Color::FromHex(0xFFFFFF));

	root->AddChild<Text>("Hello 🐸")->AddStyle<BackgroundColor>(Color::FromHex(0xFF0000));

	root->AddChild<Text>(R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vitae urna nec lorem laoreet pulvinar nec ut sem. Integer consequat nunc eu sem gravida, nec fermentum dui sagittis. Aenean ut arcu odio. Integer eu aliquet lorem. Morbi rutrum ac erat sed egestas. Sed accumsan efficitur ligula, non iaculis ligula placerat quis. Phasellus egestas tellus hendrerit velit consectetur, eget rutrum eros euismod. Nullam quis arcu ex. Morbi elementum et elit eu vehicula. Quisque eget tortor id leo laoreet egestas. Integer vitae ullamcorper sapien, congue rhoncus lacus. Suspendisse rutrum cursus est eu dictum. Fusce in leo dolor. Aenean elementum erat ornare, hendrerit ipsum vitae, facilisis ex.

Phasellus aliquet tempus ipsum, non iaculis nibh tristique at. Praesent auctor velit eget lectus placerat vestibulum. Phasellus eget diam sed turpis dictum pulvinar nec lacinia nibh. Suspendisse condimentum dolor non sem semper lobortis. Mauris nec viverra magna. Nunc mattis nunc hendrerit, vulputate leo sed, rhoncus arcu. Cras faucibus aliquam nisi, in lobortis sapien egestas condimentum. Nulla pretium lacus mi, lacinia ultrices metus accumsan ut. Morbi dui tortor, fermentum et pharetra mollis, hendrerit a augue.

Etiam ultrices pellentesque purus, vitae sollicitudin neque imperdiet non. In faucibus aliquam enim, et rutrum metus pellentesque in. In quis mattis sem. Nunc ipsum quam, dapibus vehicula leo vitae, tempus facilisis tortor. Cras condimentum justo sed massa tempus mattis eu ac odio. Fusce mattis, leo mollis laoreet elementum, est erat tincidunt odio, ac sagittis mauris ex at arcu. Praesent consequat est ut feugiat porttitor. Donec scelerisque justo eu mollis suscipit. Proin pharetra aliquet tellus vehicula venenatis. Duis ut faucibus mi. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Proin tincidunt accumsan blandit.

Morbi at erat maximus, posuere justo eu, fringilla nisi. Duis urna turpis, scelerisque eget nibh sed, sodales luctus purus. Vestibulum laoreet dignissim vehicula. In vestibulum accumsan nibh, quis sollicitudin tortor venenatis id. Aliquam auctor vel sapien sit amet gravida. Fusce euismod odio et ultricies varius. Vestibulum condimentum lacus eu mi malesuada, elementum convallis justo feugiat. Praesent ultricies nec metus quis accumsan. Nam in pellentesque ex, ac dapibus nunc. Donec eget enim eget elit blandit rhoncus.

Praesent sollicitudin lobortis consequat. Vestibulum justo erat, eleifend ac venenatis at, condimentum ac augue. Nullam rutrum venenatis ultrices. Fusce facilisis ipsum non consectetur iaculis. Interdum et malesuada fames ac ante ipsum primis in faucibus. Pellentesque non turpis sit amet nisl congue luctus. Proin vitae ante ex. Praesent ornare lorem ut massa gravida convallis. Nam tempus erat non mi euismod, nec consequat dui malesuada. Aliquam aliquam, ligula in ultricies ullamcorper, orci sapien sagittis nisl, eget feugiat ex augue sed massa.)")
		->AddStyle<BackgroundColor>(Color::FromHex(0x00FF00));

	return app->Present();
}