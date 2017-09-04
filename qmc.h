#ifndef _QMC_H_
#define _QMC_H_

#define LOGIC_MAX_BITS 12	//	入力bit最大長
#define LOGIC_MASK 0xfff //	ロジック部分を取り出すマスク

#define OUT_MASK_SHIFT 16	//	ソート時にshortで比較できるように16以上にする
#define OUT_MASK (1UL << (OUT_MASK_SHIFT))

#define MASK_TABLE_SIZE (1UL << (LOGIC_MAX_BITS))

#define LT_INDEX_NOT_USE 0
#define LT_INDEX_IN 1

#define LT_INDEX_UT_BASE 0x80

#define LT_INDEX_MASKED 2
#define LT_INDEX_TEMP_BASE 0x100

#define LT_INDEX_ 0x8000

#endif
