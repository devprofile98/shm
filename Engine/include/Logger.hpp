#ifndef SHM_LOGGER_H
#define SHM_LOGGER_H

#include "spdlog/spdlog.h"
namespace SHM::Logger {
template <typename... Args> inline void info(const char *fmt, Args &&...dpargs) { spdlog::info(fmt, dpargs...); }
template <typename... Args> inline void error(const char *fmt, Args &&...dpargs) { spdlog::error(fmt, dpargs...); }
template <typename... Args> inline void warn(const char *fmt, Args &&...dpargs) { spdlog::warn(fmt, dpargs...); }
template <typename... Args> inline void debug(const char *fmt, Args &&...dpargs) { spdlog::debug(fmt, dpargs...); }

} // namespace SHM::Logger

#endif // SHM_LOGGER_H