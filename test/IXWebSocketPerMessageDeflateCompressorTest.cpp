/*
 *  IXWebSocketPerMessageDeflateCodecTest.cpp
 *  Author: Benjamin Sergeant
 *  Copyright (c) 2020 Machine Zone. All rights reserved.
 *
 *  make build_test && build/test/ixwebsocket_unittest per-message-deflate-codec
 */

#include "IXTest.h"
#include "catch.hpp"
#include <iostream>
#include <ixwebsocket/IXWebSocketPerMessageDeflateCodec.h>
#include <string.h>

using namespace ix;

namespace ix
{
    std::string compressAndDecompress(const std::string& a)
    {
        std::string b, c;

        WebSocketPerMessageDeflateCompressor compressor;
        compressor.init(11, true);
        compressor.compress(a, b);

        WebSocketPerMessageDeflateDecompressor decompressor;
        decompressor.init(11, true);
        decompressor.decompress(b, c);

        return c;
    }

    TEST_CASE("per-message-deflate-codec", "[zlib]")
    {
        SECTION("blah")
        {
            REQUIRE(compressAndDecompress("") == "");
            REQUIRE(compressAndDecompress("foo") == "foo");
            REQUIRE(compressAndDecompress("bar") == "bar");
            REQUIRE(compressAndDecompress("asdcaseqw`21897dehqwed") == "asdcaseqw`21897dehqwed");
            REQUIRE(compressAndDecompress("/usr/local/include/ixwebsocket/IXSocketAppleSSL.h") == "/usr/local/include/ixwebsocket/IXSocketAppleSSL.h");
        }
    }

} // namespace ix
