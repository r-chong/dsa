cbuffer Params
{
    uint N;
};

RWStructuredBuffer<float> C;
StructuredBuffer<float> A;
StructuredBuffer<float> B;

[numthreads(256, 1, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
    uint i = tid.x;

    if (i < N)
    {
        C[i] = A[i] + B[i];
    }
}