
#include "Globals.h"
#include "ChunkData.h"



int main(int argc, char** argv)
{
	class cStarvationCallbacks
		: public cAllocationPool<cChunkData::sChunkSection, 1600>::cStarvationCallbacks
	{
		virtual void OnStartingUsingBuffer() {}
		virtual void OnStopUsingBuffer() {}
		virtual void OnBufferEmpty() {}
	};
	cAllocationPool<cChunkData::sChunkSection, 1600> Pool(std::auto_ptr<cAllocationPool<cChunkData::sChunkSection, 1600>::cStarvationCallbacks>(new cStarvationCallbacks()));
	{
	
		// Test first segment
		cChunkData buffer(Pool);

		BLOCKTYPE SrcBlockBuffer[16 * 16 * 256];
		memset(SrcBlockBuffer, 0x00, sizeof(SrcBlockBuffer));
		SrcBlockBuffer[7 + (4 * 16) + (5 * 16 * 16)] = 0xcd;
		buffer.SetBlockTypes(SrcBlockBuffer);
		testassert(buffer.GetBlock(7, 5, 4) == 0xcd);
	
		NIBBLETYPE SrcNibbleBuffer[16 * 16 * 256 / 2];
		memset(SrcNibbleBuffer, 0x00, sizeof(SrcNibbleBuffer));
		SrcNibbleBuffer[(6 + (1 * 16) + (2 * 16 * 16)) / 2] = 0xe;
		buffer.SetMetas(SrcNibbleBuffer);
		testassert(buffer.GetMeta(6, 2, 1) == 0xe);
	
		memset(SrcNibbleBuffer, 0x00, sizeof(SrcNibbleBuffer));
		SrcNibbleBuffer[(6 + (1 * 16) + (2 * 16 * 16)) / 2] = 0xe;
		buffer.SetBlockLight(SrcNibbleBuffer);
		testassert(buffer.GetBlockLight(6, 2, 1) == 0xe);
	
		memset(SrcNibbleBuffer, 0x00, sizeof(SrcNibbleBuffer));
		SrcNibbleBuffer[(6 + (1 * 16) + (2 * 16 * 16)) / 2] = 0xe;
		buffer.SetSkyLight(SrcNibbleBuffer);
		testassert(buffer.GetSkyLight(6, 2, 1) == 0xe);
	}
	
	{
		// test following segment
		cChunkData buffer(Pool);

		BLOCKTYPE SrcBlockBuffer[16 * 16 * 256];
		memset(SrcBlockBuffer, 0x00, sizeof(SrcBlockBuffer));
		SrcBlockBuffer[7 + (4 * 16) + (24 * 16 * 16)] = 0xcd;
		buffer.SetBlockTypes(SrcBlockBuffer);
		testassert(buffer.GetBlock(7, 24, 4) == 0xcd);
	
		NIBBLETYPE SrcNibbleBuffer[16 * 16 * 256 / 2];
		memset(SrcNibbleBuffer, 0x00, sizeof(SrcNibbleBuffer));
		SrcNibbleBuffer[(6 + (1 * 16) + (24 * 16 * 16)) / 2] = 0xe;
		buffer.SetMetas(SrcNibbleBuffer);
		testassert(buffer.GetMeta(6, 24, 1) == 0xe);
	
		memset(SrcNibbleBuffer, 0x00, sizeof(SrcNibbleBuffer));
		SrcNibbleBuffer[(6 + 1 * 16 + 24 * 16 * 16) / 2] = 0xe;
		buffer.SetBlockLight(SrcNibbleBuffer);
		testassert(buffer.GetBlockLight(6, 24, 1) == 0xe);
	
		memset(SrcNibbleBuffer, 0xff, sizeof(SrcNibbleBuffer));
		SrcNibbleBuffer[(6 + (1 * 16) + (24 * 16 * 16)) / 2] = 0xe;
		buffer.SetSkyLight(SrcNibbleBuffer);
		testassert(buffer.GetSkyLight(6, 24, 1) == 0xe);
	}
	
	{
		// test zeros
		cChunkData buffer(Pool);

		BLOCKTYPE SrcBlockBuffer[16 * 16 * 256];
		memset(SrcBlockBuffer, 0x00, sizeof(SrcBlockBuffer));
		buffer.SetBlockTypes(SrcBlockBuffer);
		testassert(buffer.GetBlock(7, 24, 4) == 0x00);
	
		NIBBLETYPE SrcNibbleBuffer[16 * 16 * 256 / 2];
		memset(SrcNibbleBuffer, 0x00, sizeof(SrcNibbleBuffer));
		buffer.SetMetas(SrcNibbleBuffer);
		testassert(buffer.GetMeta(6, 24, 1) == 0x0);
	
		memset(SrcNibbleBuffer, 0x00, sizeof(SrcNibbleBuffer));
		buffer.SetBlockLight(SrcNibbleBuffer);
		testassert(buffer.GetBlockLight(6, 24, 1) == 0x0);
	
		memset(SrcNibbleBuffer, 0xff, sizeof(SrcNibbleBuffer));
		buffer.SetSkyLight(SrcNibbleBuffer);
		testassert(buffer.GetSkyLight(6, 24, 1) == 0xf);
	}
	
	// All tests passed:
	return 0;
}

