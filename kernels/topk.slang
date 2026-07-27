// global shared memory for one thread group
groupshared float tile[256];

cbuffer Params
{
    uint N;
};

RWStructuredBuffer<float> C;
StructuredBuffer<float> A;

[numthreads(256, 1, 1)]
void main(uint3 tid : SV_DispatchThreadID, uint3 gtid : SV_GroupThreadID, uint3 gid : SV_GroupID)
{
    uint i = tid.x;
    float x;

    // No action performed, we simply load one value
    if (i >= N) {
        // -infinity
        x = -3.402823466e+38f;    
    } else {
        x = A[i];
    }

    tile[gtid.x] = x;

    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 128) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 128];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 128];
    }
    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 64) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 64];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 64];
    }
    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 32) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 32];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 32];
    }
    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 16) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 16];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 16];
    }
    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 8) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 8];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 8];
    }
    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 4) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 4];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 4];
    }
    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 2) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 2];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 2];
    }
    GroupMemoryBarrierWithGroupSync();
    if (gtid.x < 1) {
        bool comp = tile[gtid.x] >= tile[gtid.x + 1];

        tile[gtid.x] = comp ? tile[gtid.x] : tile[gtid.x + 1];
    }
    GroupMemoryBarrierWithGroupSync();

    if (gtid.x == 0) {
        C[gid.x] = tile[0];
    }
}   