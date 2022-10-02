#include "plugin.h"

#include <mp/host/host.h>
#include <mp/log/intf_log.h>
#include <xputil/impl_intfs.h>
#include <base/io/log/Log.h>

#include <map>

using namespace xp;
using namespace mp::host;

namespace xmrig::plugin
{
    namespace
    {
        auto_ref<IBus> srv_;

        ml::level_t convert_level(Log::Level v)
        {
            static std::map<Log::Level, ml::level_t> s_maps = {
                {Log::Level::NONE, ml::level_t::info},
                {Log::Level::EMERG, ml::level_t::fatal},
                {Log::Level::ALERT, ml::level_t::warn},
                {Log::Level::CRIT, ml::level_t::fatal},
                {Log::Level::ERR, ml::level_t::error},
                {Log::Level::WARNING, ml::level_t::warn},
                {Log::Level::NOTICE, ml::level_t::info},
                {Log::Level::INFO, ml::level_t::info},
                {Log::Level::DEBUG, ml::level_t::trace},
            };

            return s_maps.at(v);
        }

        Log::Level convert_level(ml::level_t v)
        {
            static std::map<ml::level_t, Log::Level> s_maps = {
                {ml::level_t::trace, Log::Level::DEBUG},
                {ml::level_t::info, Log::Level::INFO},
                {ml::level_t::warn, Log::Level::WARNING},
                {ml::level_t::error, Log::Level::ERR},
                {ml::level_t::fatal, Log::Level::EMERG},
            };
            return s_maps.at(v);
        }

        class MyLog : public xp::TInterfaceEx<mp::log::ILog>
        {
        public:
            // log is enabled?
            bool enabled() override { return true; }
            // output log message
            void print(const char *msg, const ml::message_attr_t *attr) override
            {
                xmrig::Log::print(convert_level(attr->level), "%s[%s:%i] %s: %s", attr->module, attr->src, attr->line, attr->func, msg);
            }
        };
    }

    void init(Log::Level level)
    {
        srv_ = new xp::TBus(1);
        srv_->connect(new MyLog());

        host_config_t cfg;
        cfg.name = "xmrig";
        cfg.log_level = convert_level(level);
        cfg.ext_bus = srv_;
        mp::host::init(cfg);
    }

    void finish()
    {
        mp::host::finish();
        srv_.clear();
    }
}