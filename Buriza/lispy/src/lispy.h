#pragma once
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "userenv.lib")

extern "C" {
    namespace lispy {
        void interpret();
    }
}
