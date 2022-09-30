#ifndef XMRIG_PLUGIN_H
#define XMRIG_PLUGIN_H

namespace xmrig::plugin
{
    void init();
    void finish();

    class PluginSetup
    {
    public:
        PluginSetup() { init(); }
        ~PluginSetup() { finish(); }
    };
}

#endif