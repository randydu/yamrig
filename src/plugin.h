#ifndef XMRIG_PLUGIN_H
#define XMRIG_PLUGIN_H

#include "base/io/log/Log.h"

namespace xmrig::plugin
{
    void init(Log::Level level);
    void finish();

    class PluginSetup
    {
    public:
        PluginSetup(Log::Level level) { init(level); }
        ~PluginSetup() { finish(); }
    };
}

#endif