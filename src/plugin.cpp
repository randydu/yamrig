#include "plugin.h"

#include <mp/host/host.h>

using namespace mp::host;

namespace xmrig::plugin
{
    void init()
    {
        host_config_t cfg;
        cfg.name = "xmrig";
        cfg.log_level = mp::log::logger_t::LEVEL_ALL;
        cfg.ext_bus = nullptr;
        mp::host::init(cfg);
    }
    void finish()
    {
        mp::host::finish();
    }
}