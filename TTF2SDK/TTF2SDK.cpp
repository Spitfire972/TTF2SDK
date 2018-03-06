#include "stdafx.h"

TTF2SDK::TTF2SDK()
{
    auto logger = spdlog::get("logger");
    //throw std::exception("Wat");
    logger->info("TTF2SDK Initialised");
}

TTF2SDK& TTF2SDK::GetInstance()
{
    static TTF2SDK instance;
    return instance;
}
