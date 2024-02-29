#include "MACRO.h"

XMFLOAT3 NormalizeF3(XMFLOAT3 v)
{
    XMVECTOR vec = {};

    vec = XMLoadFloat3(&v);
    vec = XMVector3Normalize(vec);

    static XMFLOAT3 ret = {};

    XMStoreFloat3(&ret, vec);

    return ret;
}

uint8_t PID_NUM = 0; 