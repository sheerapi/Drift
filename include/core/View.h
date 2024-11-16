#pragma once

namespace Drift
{
    class View
    {
    public:
        virtual void Present() {};
        virtual void Update() {};
        virtual void Render() {};

        [[nodiscard]] inline auto IsEnabled() const -> bool
        {
            return _enabled;
        }

        inline void SetEnabled(bool enabled)
        {
            _enabled = enabled;
        }

    private:
        bool _enabled{true};
    };
}