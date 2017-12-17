#pragma once

#include <iosfwd>

#include "ip.h"

void read_ip_from_stream( ip_pool_t& ip_pool, std::istream& istr );
