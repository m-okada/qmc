int mask_table[4096]={0x000, 
0x001, 0x002, 0x004, 0x008, 0x010, 0x020, 0x040, 0x080, 0x100, 0x200, 0x400, 0x800, 0x003, 0x005, 0x006, 0x009, 
0x00a, 0x00c, 0x011, 0x012, 0x014, 0x018, 0x021, 0x022, 0x024, 0x028, 0x030, 0x041, 0x042, 0x044, 0x048, 0x050, 
0x060, 0x081, 0x082, 0x084, 0x088, 0x090, 0x0a0, 0x0c0, 0x101, 0x102, 0x104, 0x108, 0x110, 0x120, 0x140, 0x180, 
0x201, 0x202, 0x204, 0x208, 0x210, 0x220, 0x240, 0x280, 0x300, 0x401, 0x402, 0x404, 0x408, 0x410, 0x420, 0x440, 
0x480, 0x500, 0x600, 0x801, 0x802, 0x804, 0x808, 0x810, 0x820, 0x840, 0x880, 0x900, 0xa00, 0xc00, 0x007, 0x00b, 
0x00d, 0x00e, 0x013, 0x015, 0x016, 0x019, 0x01a, 0x01c, 0x023, 0x025, 0x026, 0x029, 0x02a, 0x02c, 0x031, 0x032, 
0x034, 0x038, 0x043, 0x045, 0x046, 0x049, 0x04a, 0x04c, 0x051, 0x052, 0x054, 0x058, 0x061, 0x062, 0x064, 0x068, 
0x070, 0x083, 0x085, 0x086, 0x089, 0x08a, 0x08c, 0x091, 0x092, 0x094, 0x098, 0x0a1, 0x0a2, 0x0a4, 0x0a8, 0x0b0, 
0x0c1, 0x0c2, 0x0c4, 0x0c8, 0x0d0, 0x0e0, 0x103, 0x105, 0x106, 0x109, 0x10a, 0x10c, 0x111, 0x112, 0x114, 0x118, 
0x121, 0x122, 0x124, 0x128, 0x130, 0x141, 0x142, 0x144, 0x148, 0x150, 0x160, 0x181, 0x182, 0x184, 0x188, 0x190, 
0x1a0, 0x1c0, 0x203, 0x205, 0x206, 0x209, 0x20a, 0x20c, 0x211, 0x212, 0x214, 0x218, 0x221, 0x222, 0x224, 0x228, 
0x230, 0x241, 0x242, 0x244, 0x248, 0x250, 0x260, 0x281, 0x282, 0x284, 0x288, 0x290, 0x2a0, 0x2c0, 0x301, 0x302, 
0x304, 0x308, 0x310, 0x320, 0x340, 0x380, 0x403, 0x405, 0x406, 0x409, 0x40a, 0x40c, 0x411, 0x412, 0x414, 0x418, 
0x421, 0x422, 0x424, 0x428, 0x430, 0x441, 0x442, 0x444, 0x448, 0x450, 0x460, 0x481, 0x482, 0x484, 0x488, 0x490, 
0x4a0, 0x4c0, 0x501, 0x502, 0x504, 0x508, 0x510, 0x520, 0x540, 0x580, 0x601, 0x602, 0x604, 0x608, 0x610, 0x620, 
0x640, 0x680, 0x700, 0x803, 0x805, 0x806, 0x809, 0x80a, 0x80c, 0x811, 0x812, 0x814, 0x818, 0x821, 0x822, 0x824, 
0x828, 0x830, 0x841, 0x842, 0x844, 0x848, 0x850, 0x860, 0x881, 0x882, 0x884, 0x888, 0x890, 0x8a0, 0x8c0, 0x901, 
0x902, 0x904, 0x908, 0x910, 0x920, 0x940, 0x980, 0xa01, 0xa02, 0xa04, 0xa08, 0xa10, 0xa20, 0xa40, 0xa80, 0xb00, 
0xc01, 0xc02, 0xc04, 0xc08, 0xc10, 0xc20, 0xc40, 0xc80, 0xd00, 0xe00, 0x00f, 0x017, 0x01b, 0x01d, 0x01e, 0x027, 
0x02b, 0x02d, 0x02e, 0x033, 0x035, 0x036, 0x039, 0x03a, 0x03c, 0x047, 0x04b, 0x04d, 0x04e, 0x053, 0x055, 0x056, 
0x059, 0x05a, 0x05c, 0x063, 0x065, 0x066, 0x069, 0x06a, 0x06c, 0x071, 0x072, 0x074, 0x078, 0x087, 0x08b, 0x08d, 
0x08e, 0x093, 0x095, 0x096, 0x099, 0x09a, 0x09c, 0x0a3, 0x0a5, 0x0a6, 0x0a9, 0x0aa, 0x0ac, 0x0b1, 0x0b2, 0x0b4, 
0x0b8, 0x0c3, 0x0c5, 0x0c6, 0x0c9, 0x0ca, 0x0cc, 0x0d1, 0x0d2, 0x0d4, 0x0d8, 0x0e1, 0x0e2, 0x0e4, 0x0e8, 0x0f0, 
0x107, 0x10b, 0x10d, 0x10e, 0x113, 0x115, 0x116, 0x119, 0x11a, 0x11c, 0x123, 0x125, 0x126, 0x129, 0x12a, 0x12c, 
0x131, 0x132, 0x134, 0x138, 0x143, 0x145, 0x146, 0x149, 0x14a, 0x14c, 0x151, 0x152, 0x154, 0x158, 0x161, 0x162, 
0x164, 0x168, 0x170, 0x183, 0x185, 0x186, 0x189, 0x18a, 0x18c, 0x191, 0x192, 0x194, 0x198, 0x1a1, 0x1a2, 0x1a4, 
0x1a8, 0x1b0, 0x1c1, 0x1c2, 0x1c4, 0x1c8, 0x1d0, 0x1e0, 0x207, 0x20b, 0x20d, 0x20e, 0x213, 0x215, 0x216, 0x219, 
0x21a, 0x21c, 0x223, 0x225, 0x226, 0x229, 0x22a, 0x22c, 0x231, 0x232, 0x234, 0x238, 0x243, 0x245, 0x246, 0x249, 
0x24a, 0x24c, 0x251, 0x252, 0x254, 0x258, 0x261, 0x262, 0x264, 0x268, 0x270, 0x283, 0x285, 0x286, 0x289, 0x28a, 
0x28c, 0x291, 0x292, 0x294, 0x298, 0x2a1, 0x2a2, 0x2a4, 0x2a8, 0x2b0, 0x2c1, 0x2c2, 0x2c4, 0x2c8, 0x2d0, 0x2e0, 
0x303, 0x305, 0x306, 0x309, 0x30a, 0x30c, 0x311, 0x312, 0x314, 0x318, 0x321, 0x322, 0x324, 0x328, 0x330, 0x341, 
0x342, 0x344, 0x348, 0x350, 0x360, 0x381, 0x382, 0x384, 0x388, 0x390, 0x3a0, 0x3c0, 0x407, 0x40b, 0x40d, 0x40e, 
0x413, 0x415, 0x416, 0x419, 0x41a, 0x41c, 0x423, 0x425, 0x426, 0x429, 0x42a, 0x42c, 0x431, 0x432, 0x434, 0x438, 
0x443, 0x445, 0x446, 0x449, 0x44a, 0x44c, 0x451, 0x452, 0x454, 0x458, 0x461, 0x462, 0x464, 0x468, 0x470, 0x483, 
0x485, 0x486, 0x489, 0x48a, 0x48c, 0x491, 0x492, 0x494, 0x498, 0x4a1, 0x4a2, 0x4a4, 0x4a8, 0x4b0, 0x4c1, 0x4c2, 
0x4c4, 0x4c8, 0x4d0, 0x4e0, 0x503, 0x505, 0x506, 0x509, 0x50a, 0x50c, 0x511, 0x512, 0x514, 0x518, 0x521, 0x522, 
0x524, 0x528, 0x530, 0x541, 0x542, 0x544, 0x548, 0x550, 0x560, 0x581, 0x582, 0x584, 0x588, 0x590, 0x5a0, 0x5c0, 
0x603, 0x605, 0x606, 0x609, 0x60a, 0x60c, 0x611, 0x612, 0x614, 0x618, 0x621, 0x622, 0x624, 0x628, 0x630, 0x641, 
0x642, 0x644, 0x648, 0x650, 0x660, 0x681, 0x682, 0x684, 0x688, 0x690, 0x6a0, 0x6c0, 0x701, 0x702, 0x704, 0x708, 
0x710, 0x720, 0x740, 0x780, 0x807, 0x80b, 0x80d, 0x80e, 0x813, 0x815, 0x816, 0x819, 0x81a, 0x81c, 0x823, 0x825, 
0x826, 0x829, 0x82a, 0x82c, 0x831, 0x832, 0x834, 0x838, 0x843, 0x845, 0x846, 0x849, 0x84a, 0x84c, 0x851, 0x852, 
0x854, 0x858, 0x861, 0x862, 0x864, 0x868, 0x870, 0x883, 0x885, 0x886, 0x889, 0x88a, 0x88c, 0x891, 0x892, 0x894, 
0x898, 0x8a1, 0x8a2, 0x8a4, 0x8a8, 0x8b0, 0x8c1, 0x8c2, 0x8c4, 0x8c8, 0x8d0, 0x8e0, 0x903, 0x905, 0x906, 0x909, 
0x90a, 0x90c, 0x911, 0x912, 0x914, 0x918, 0x921, 0x922, 0x924, 0x928, 0x930, 0x941, 0x942, 0x944, 0x948, 0x950, 
0x960, 0x981, 0x982, 0x984, 0x988, 0x990, 0x9a0, 0x9c0, 0xa03, 0xa05, 0xa06, 0xa09, 0xa0a, 0xa0c, 0xa11, 0xa12, 
0xa14, 0xa18, 0xa21, 0xa22, 0xa24, 0xa28, 0xa30, 0xa41, 0xa42, 0xa44, 0xa48, 0xa50, 0xa60, 0xa81, 0xa82, 0xa84, 
0xa88, 0xa90, 0xaa0, 0xac0, 0xb01, 0xb02, 0xb04, 0xb08, 0xb10, 0xb20, 0xb40, 0xb80, 0xc03, 0xc05, 0xc06, 0xc09, 
0xc0a, 0xc0c, 0xc11, 0xc12, 0xc14, 0xc18, 0xc21, 0xc22, 0xc24, 0xc28, 0xc30, 0xc41, 0xc42, 0xc44, 0xc48, 0xc50, 
0xc60, 0xc81, 0xc82, 0xc84, 0xc88, 0xc90, 0xca0, 0xcc0, 0xd01, 0xd02, 0xd04, 0xd08, 0xd10, 0xd20, 0xd40, 0xd80, 
0xe01, 0xe02, 0xe04, 0xe08, 0xe10, 0xe20, 0xe40, 0xe80, 0xf00, 0x01f, 0x02f, 0x037, 0x03b, 0x03d, 0x03e, 0x04f, 
0x057, 0x05b, 0x05d, 0x05e, 0x067, 0x06b, 0x06d, 0x06e, 0x073, 0x075, 0x076, 0x079, 0x07a, 0x07c, 0x08f, 0x097, 
0x09b, 0x09d, 0x09e, 0x0a7, 0x0ab, 0x0ad, 0x0ae, 0x0b3, 0x0b5, 0x0b6, 0x0b9, 0x0ba, 0x0bc, 0x0c7, 0x0cb, 0x0cd, 
0x0ce, 0x0d3, 0x0d5, 0x0d6, 0x0d9, 0x0da, 0x0dc, 0x0e3, 0x0e5, 0x0e6, 0x0e9, 0x0ea, 0x0ec, 0x0f1, 0x0f2, 0x0f4, 
0x0f8, 0x10f, 0x117, 0x11b, 0x11d, 0x11e, 0x127, 0x12b, 0x12d, 0x12e, 0x133, 0x135, 0x136, 0x139, 0x13a, 0x13c, 
0x147, 0x14b, 0x14d, 0x14e, 0x153, 0x155, 0x156, 0x159, 0x15a, 0x15c, 0x163, 0x165, 0x166, 0x169, 0x16a, 0x16c, 
0x171, 0x172, 0x174, 0x178, 0x187, 0x18b, 0x18d, 0x18e, 0x193, 0x195, 0x196, 0x199, 0x19a, 0x19c, 0x1a3, 0x1a5, 
0x1a6, 0x1a9, 0x1aa, 0x1ac, 0x1b1, 0x1b2, 0x1b4, 0x1b8, 0x1c3, 0x1c5, 0x1c6, 0x1c9, 0x1ca, 0x1cc, 0x1d1, 0x1d2, 
0x1d4, 0x1d8, 0x1e1, 0x1e2, 0x1e4, 0x1e8, 0x1f0, 0x20f, 0x217, 0x21b, 0x21d, 0x21e, 0x227, 0x22b, 0x22d, 0x22e, 
0x233, 0x235, 0x236, 0x239, 0x23a, 0x23c, 0x247, 0x24b, 0x24d, 0x24e, 0x253, 0x255, 0x256, 0x259, 0x25a, 0x25c, 
0x263, 0x265, 0x266, 0x269, 0x26a, 0x26c, 0x271, 0x272, 0x274, 0x278, 0x287, 0x28b, 0x28d, 0x28e, 0x293, 0x295, 
0x296, 0x299, 0x29a, 0x29c, 0x2a3, 0x2a5, 0x2a6, 0x2a9, 0x2aa, 0x2ac, 0x2b1, 0x2b2, 0x2b4, 0x2b8, 0x2c3, 0x2c5, 
0x2c6, 0x2c9, 0x2ca, 0x2cc, 0x2d1, 0x2d2, 0x2d4, 0x2d8, 0x2e1, 0x2e2, 0x2e4, 0x2e8, 0x2f0, 0x307, 0x30b, 0x30d, 
0x30e, 0x313, 0x315, 0x316, 0x319, 0x31a, 0x31c, 0x323, 0x325, 0x326, 0x329, 0x32a, 0x32c, 0x331, 0x332, 0x334, 
0x338, 0x343, 0x345, 0x346, 0x349, 0x34a, 0x34c, 0x351, 0x352, 0x354, 0x358, 0x361, 0x362, 0x364, 0x368, 0x370, 
0x383, 0x385, 0x386, 0x389, 0x38a, 0x38c, 0x391, 0x392, 0x394, 0x398, 0x3a1, 0x3a2, 0x3a4, 0x3a8, 0x3b0, 0x3c1, 
0x3c2, 0x3c4, 0x3c8, 0x3d0, 0x3e0, 0x40f, 0x417, 0x41b, 0x41d, 0x41e, 0x427, 0x42b, 0x42d, 0x42e, 0x433, 0x435, 
0x436, 0x439, 0x43a, 0x43c, 0x447, 0x44b, 0x44d, 0x44e, 0x453, 0x455, 0x456, 0x459, 0x45a, 0x45c, 0x463, 0x465, 
0x466, 0x469, 0x46a, 0x46c, 0x471, 0x472, 0x474, 0x478, 0x487, 0x48b, 0x48d, 0x48e, 0x493, 0x495, 0x496, 0x499, 
0x49a, 0x49c, 0x4a3, 0x4a5, 0x4a6, 0x4a9, 0x4aa, 0x4ac, 0x4b1, 0x4b2, 0x4b4, 0x4b8, 0x4c3, 0x4c5, 0x4c6, 0x4c9, 
0x4ca, 0x4cc, 0x4d1, 0x4d2, 0x4d4, 0x4d8, 0x4e1, 0x4e2, 0x4e4, 0x4e8, 0x4f0, 0x507, 0x50b, 0x50d, 0x50e, 0x513, 
0x515, 0x516, 0x519, 0x51a, 0x51c, 0x523, 0x525, 0x526, 0x529, 0x52a, 0x52c, 0x531, 0x532, 0x534, 0x538, 0x543, 
0x545, 0x546, 0x549, 0x54a, 0x54c, 0x551, 0x552, 0x554, 0x558, 0x561, 0x562, 0x564, 0x568, 0x570, 0x583, 0x585, 
0x586, 0x589, 0x58a, 0x58c, 0x591, 0x592, 0x594, 0x598, 0x5a1, 0x5a2, 0x5a4, 0x5a8, 0x5b0, 0x5c1, 0x5c2, 0x5c4, 
0x5c8, 0x5d0, 0x5e0, 0x607, 0x60b, 0x60d, 0x60e, 0x613, 0x615, 0x616, 0x619, 0x61a, 0x61c, 0x623, 0x625, 0x626, 
0x629, 0x62a, 0x62c, 0x631, 0x632, 0x634, 0x638, 0x643, 0x645, 0x646, 0x649, 0x64a, 0x64c, 0x651, 0x652, 0x654, 
0x658, 0x661, 0x662, 0x664, 0x668, 0x670, 0x683, 0x685, 0x686, 0x689, 0x68a, 0x68c, 0x691, 0x692, 0x694, 0x698, 
0x6a1, 0x6a2, 0x6a4, 0x6a8, 0x6b0, 0x6c1, 0x6c2, 0x6c4, 0x6c8, 0x6d0, 0x6e0, 0x703, 0x705, 0x706, 0x709, 0x70a, 
0x70c, 0x711, 0x712, 0x714, 0x718, 0x721, 0x722, 0x724, 0x728, 0x730, 0x741, 0x742, 0x744, 0x748, 0x750, 0x760, 
0x781, 0x782, 0x784, 0x788, 0x790, 0x7a0, 0x7c0, 0x80f, 0x817, 0x81b, 0x81d, 0x81e, 0x827, 0x82b, 0x82d, 0x82e, 
0x833, 0x835, 0x836, 0x839, 0x83a, 0x83c, 0x847, 0x84b, 0x84d, 0x84e, 0x853, 0x855, 0x856, 0x859, 0x85a, 0x85c, 
0x863, 0x865, 0x866, 0x869, 0x86a, 0x86c, 0x871, 0x872, 0x874, 0x878, 0x887, 0x88b, 0x88d, 0x88e, 0x893, 0x895, 
0x896, 0x899, 0x89a, 0x89c, 0x8a3, 0x8a5, 0x8a6, 0x8a9, 0x8aa, 0x8ac, 0x8b1, 0x8b2, 0x8b4, 0x8b8, 0x8c3, 0x8c5, 
0x8c6, 0x8c9, 0x8ca, 0x8cc, 0x8d1, 0x8d2, 0x8d4, 0x8d8, 0x8e1, 0x8e2, 0x8e4, 0x8e8, 0x8f0, 0x907, 0x90b, 0x90d, 
0x90e, 0x913, 0x915, 0x916, 0x919, 0x91a, 0x91c, 0x923, 0x925, 0x926, 0x929, 0x92a, 0x92c, 0x931, 0x932, 0x934, 
0x938, 0x943, 0x945, 0x946, 0x949, 0x94a, 0x94c, 0x951, 0x952, 0x954, 0x958, 0x961, 0x962, 0x964, 0x968, 0x970, 
0x983, 0x985, 0x986, 0x989, 0x98a, 0x98c, 0x991, 0x992, 0x994, 0x998, 0x9a1, 0x9a2, 0x9a4, 0x9a8, 0x9b0, 0x9c1, 
0x9c2, 0x9c4, 0x9c8, 0x9d0, 0x9e0, 0xa07, 0xa0b, 0xa0d, 0xa0e, 0xa13, 0xa15, 0xa16, 0xa19, 0xa1a, 0xa1c, 0xa23, 
0xa25, 0xa26, 0xa29, 0xa2a, 0xa2c, 0xa31, 0xa32, 0xa34, 0xa38, 0xa43, 0xa45, 0xa46, 0xa49, 0xa4a, 0xa4c, 0xa51, 
0xa52, 0xa54, 0xa58, 0xa61, 0xa62, 0xa64, 0xa68, 0xa70, 0xa83, 0xa85, 0xa86, 0xa89, 0xa8a, 0xa8c, 0xa91, 0xa92, 
0xa94, 0xa98, 0xaa1, 0xaa2, 0xaa4, 0xaa8, 0xab0, 0xac1, 0xac2, 0xac4, 0xac8, 0xad0, 0xae0, 0xb03, 0xb05, 0xb06, 
0xb09, 0xb0a, 0xb0c, 0xb11, 0xb12, 0xb14, 0xb18, 0xb21, 0xb22, 0xb24, 0xb28, 0xb30, 0xb41, 0xb42, 0xb44, 0xb48, 
0xb50, 0xb60, 0xb81, 0xb82, 0xb84, 0xb88, 0xb90, 0xba0, 0xbc0, 0xc07, 0xc0b, 0xc0d, 0xc0e, 0xc13, 0xc15, 0xc16, 
0xc19, 0xc1a, 0xc1c, 0xc23, 0xc25, 0xc26, 0xc29, 0xc2a, 0xc2c, 0xc31, 0xc32, 0xc34, 0xc38, 0xc43, 0xc45, 0xc46, 
0xc49, 0xc4a, 0xc4c, 0xc51, 0xc52, 0xc54, 0xc58, 0xc61, 0xc62, 0xc64, 0xc68, 0xc70, 0xc83, 0xc85, 0xc86, 0xc89, 
0xc8a, 0xc8c, 0xc91, 0xc92, 0xc94, 0xc98, 0xca1, 0xca2, 0xca4, 0xca8, 0xcb0, 0xcc1, 0xcc2, 0xcc4, 0xcc8, 0xcd0, 
0xce0, 0xd03, 0xd05, 0xd06, 0xd09, 0xd0a, 0xd0c, 0xd11, 0xd12, 0xd14, 0xd18, 0xd21, 0xd22, 0xd24, 0xd28, 0xd30, 
0xd41, 0xd42, 0xd44, 0xd48, 0xd50, 0xd60, 0xd81, 0xd82, 0xd84, 0xd88, 0xd90, 0xda0, 0xdc0, 0xe03, 0xe05, 0xe06, 
0xe09, 0xe0a, 0xe0c, 0xe11, 0xe12, 0xe14, 0xe18, 0xe21, 0xe22, 0xe24, 0xe28, 0xe30, 0xe41, 0xe42, 0xe44, 0xe48, 
0xe50, 0xe60, 0xe81, 0xe82, 0xe84, 0xe88, 0xe90, 0xea0, 0xec0, 0xf01, 0xf02, 0xf04, 0xf08, 0xf10, 0xf20, 0xf40, 
0xf80, 0x03f, 0x05f, 0x06f, 0x077, 0x07b, 0x07d, 0x07e, 0x09f, 0x0af, 0x0b7, 0x0bb, 0x0bd, 0x0be, 0x0cf, 0x0d7, 
0x0db, 0x0dd, 0x0de, 0x0e7, 0x0eb, 0x0ed, 0x0ee, 0x0f3, 0x0f5, 0x0f6, 0x0f9, 0x0fa, 0x0fc, 0x11f, 0x12f, 0x137, 
0x13b, 0x13d, 0x13e, 0x14f, 0x157, 0x15b, 0x15d, 0x15e, 0x167, 0x16b, 0x16d, 0x16e, 0x173, 0x175, 0x176, 0x179, 
0x17a, 0x17c, 0x18f, 0x197, 0x19b, 0x19d, 0x19e, 0x1a7, 0x1ab, 0x1ad, 0x1ae, 0x1b3, 0x1b5, 0x1b6, 0x1b9, 0x1ba, 
0x1bc, 0x1c7, 0x1cb, 0x1cd, 0x1ce, 0x1d3, 0x1d5, 0x1d6, 0x1d9, 0x1da, 0x1dc, 0x1e3, 0x1e5, 0x1e6, 0x1e9, 0x1ea, 
0x1ec, 0x1f1, 0x1f2, 0x1f4, 0x1f8, 0x21f, 0x22f, 0x237, 0x23b, 0x23d, 0x23e, 0x24f, 0x257, 0x25b, 0x25d, 0x25e, 
0x267, 0x26b, 0x26d, 0x26e, 0x273, 0x275, 0x276, 0x279, 0x27a, 0x27c, 0x28f, 0x297, 0x29b, 0x29d, 0x29e, 0x2a7, 
0x2ab, 0x2ad, 0x2ae, 0x2b3, 0x2b5, 0x2b6, 0x2b9, 0x2ba, 0x2bc, 0x2c7, 0x2cb, 0x2cd, 0x2ce, 0x2d3, 0x2d5, 0x2d6, 
0x2d9, 0x2da, 0x2dc, 0x2e3, 0x2e5, 0x2e6, 0x2e9, 0x2ea, 0x2ec, 0x2f1, 0x2f2, 0x2f4, 0x2f8, 0x30f, 0x317, 0x31b, 
0x31d, 0x31e, 0x327, 0x32b, 0x32d, 0x32e, 0x333, 0x335, 0x336, 0x339, 0x33a, 0x33c, 0x347, 0x34b, 0x34d, 0x34e, 
0x353, 0x355, 0x356, 0x359, 0x35a, 0x35c, 0x363, 0x365, 0x366, 0x369, 0x36a, 0x36c, 0x371, 0x372, 0x374, 0x378, 
0x387, 0x38b, 0x38d, 0x38e, 0x393, 0x395, 0x396, 0x399, 0x39a, 0x39c, 0x3a3, 0x3a5, 0x3a6, 0x3a9, 0x3aa, 0x3ac, 
0x3b1, 0x3b2, 0x3b4, 0x3b8, 0x3c3, 0x3c5, 0x3c6, 0x3c9, 0x3ca, 0x3cc, 0x3d1, 0x3d2, 0x3d4, 0x3d8, 0x3e1, 0x3e2, 
0x3e4, 0x3e8, 0x3f0, 0x41f, 0x42f, 0x437, 0x43b, 0x43d, 0x43e, 0x44f, 0x457, 0x45b, 0x45d, 0x45e, 0x467, 0x46b, 
0x46d, 0x46e, 0x473, 0x475, 0x476, 0x479, 0x47a, 0x47c, 0x48f, 0x497, 0x49b, 0x49d, 0x49e, 0x4a7, 0x4ab, 0x4ad, 
0x4ae, 0x4b3, 0x4b5, 0x4b6, 0x4b9, 0x4ba, 0x4bc, 0x4c7, 0x4cb, 0x4cd, 0x4ce, 0x4d3, 0x4d5, 0x4d6, 0x4d9, 0x4da, 
0x4dc, 0x4e3, 0x4e5, 0x4e6, 0x4e9, 0x4ea, 0x4ec, 0x4f1, 0x4f2, 0x4f4, 0x4f8, 0x50f, 0x517, 0x51b, 0x51d, 0x51e, 
0x527, 0x52b, 0x52d, 0x52e, 0x533, 0x535, 0x536, 0x539, 0x53a, 0x53c, 0x547, 0x54b, 0x54d, 0x54e, 0x553, 0x555, 
0x556, 0x559, 0x55a, 0x55c, 0x563, 0x565, 0x566, 0x569, 0x56a, 0x56c, 0x571, 0x572, 0x574, 0x578, 0x587, 0x58b, 
0x58d, 0x58e, 0x593, 0x595, 0x596, 0x599, 0x59a, 0x59c, 0x5a3, 0x5a5, 0x5a6, 0x5a9, 0x5aa, 0x5ac, 0x5b1, 0x5b2, 
0x5b4, 0x5b8, 0x5c3, 0x5c5, 0x5c6, 0x5c9, 0x5ca, 0x5cc, 0x5d1, 0x5d2, 0x5d4, 0x5d8, 0x5e1, 0x5e2, 0x5e4, 0x5e8, 
0x5f0, 0x60f, 0x617, 0x61b, 0x61d, 0x61e, 0x627, 0x62b, 0x62d, 0x62e, 0x633, 0x635, 0x636, 0x639, 0x63a, 0x63c, 
0x647, 0x64b, 0x64d, 0x64e, 0x653, 0x655, 0x656, 0x659, 0x65a, 0x65c, 0x663, 0x665, 0x666, 0x669, 0x66a, 0x66c, 
0x671, 0x672, 0x674, 0x678, 0x687, 0x68b, 0x68d, 0x68e, 0x693, 0x695, 0x696, 0x699, 0x69a, 0x69c, 0x6a3, 0x6a5, 
0x6a6, 0x6a9, 0x6aa, 0x6ac, 0x6b1, 0x6b2, 0x6b4, 0x6b8, 0x6c3, 0x6c5, 0x6c6, 0x6c9, 0x6ca, 0x6cc, 0x6d1, 0x6d2, 
0x6d4, 0x6d8, 0x6e1, 0x6e2, 0x6e4, 0x6e8, 0x6f0, 0x707, 0x70b, 0x70d, 0x70e, 0x713, 0x715, 0x716, 0x719, 0x71a, 
0x71c, 0x723, 0x725, 0x726, 0x729, 0x72a, 0x72c, 0x731, 0x732, 0x734, 0x738, 0x743, 0x745, 0x746, 0x749, 0x74a, 
0x74c, 0x751, 0x752, 0x754, 0x758, 0x761, 0x762, 0x764, 0x768, 0x770, 0x783, 0x785, 0x786, 0x789, 0x78a, 0x78c, 
0x791, 0x792, 0x794, 0x798, 0x7a1, 0x7a2, 0x7a4, 0x7a8, 0x7b0, 0x7c1, 0x7c2, 0x7c4, 0x7c8, 0x7d0, 0x7e0, 0x81f, 
0x82f, 0x837, 0x83b, 0x83d, 0x83e, 0x84f, 0x857, 0x85b, 0x85d, 0x85e, 0x867, 0x86b, 0x86d, 0x86e, 0x873, 0x875, 
0x876, 0x879, 0x87a, 0x87c, 0x88f, 0x897, 0x89b, 0x89d, 0x89e, 0x8a7, 0x8ab, 0x8ad, 0x8ae, 0x8b3, 0x8b5, 0x8b6, 
0x8b9, 0x8ba, 0x8bc, 0x8c7, 0x8cb, 0x8cd, 0x8ce, 0x8d3, 0x8d5, 0x8d6, 0x8d9, 0x8da, 0x8dc, 0x8e3, 0x8e5, 0x8e6, 
0x8e9, 0x8ea, 0x8ec, 0x8f1, 0x8f2, 0x8f4, 0x8f8, 0x90f, 0x917, 0x91b, 0x91d, 0x91e, 0x927, 0x92b, 0x92d, 0x92e, 
0x933, 0x935, 0x936, 0x939, 0x93a, 0x93c, 0x947, 0x94b, 0x94d, 0x94e, 0x953, 0x955, 0x956, 0x959, 0x95a, 0x95c, 
0x963, 0x965, 0x966, 0x969, 0x96a, 0x96c, 0x971, 0x972, 0x974, 0x978, 0x987, 0x98b, 0x98d, 0x98e, 0x993, 0x995, 
0x996, 0x999, 0x99a, 0x99c, 0x9a3, 0x9a5, 0x9a6, 0x9a9, 0x9aa, 0x9ac, 0x9b1, 0x9b2, 0x9b4, 0x9b8, 0x9c3, 0x9c5, 
0x9c6, 0x9c9, 0x9ca, 0x9cc, 0x9d1, 0x9d2, 0x9d4, 0x9d8, 0x9e1, 0x9e2, 0x9e4, 0x9e8, 0x9f0, 0xa0f, 0xa17, 0xa1b, 
0xa1d, 0xa1e, 0xa27, 0xa2b, 0xa2d, 0xa2e, 0xa33, 0xa35, 0xa36, 0xa39, 0xa3a, 0xa3c, 0xa47, 0xa4b, 0xa4d, 0xa4e, 
0xa53, 0xa55, 0xa56, 0xa59, 0xa5a, 0xa5c, 0xa63, 0xa65, 0xa66, 0xa69, 0xa6a, 0xa6c, 0xa71, 0xa72, 0xa74, 0xa78, 
0xa87, 0xa8b, 0xa8d, 0xa8e, 0xa93, 0xa95, 0xa96, 0xa99, 0xa9a, 0xa9c, 0xaa3, 0xaa5, 0xaa6, 0xaa9, 0xaaa, 0xaac, 
0xab1, 0xab2, 0xab4, 0xab8, 0xac3, 0xac5, 0xac6, 0xac9, 0xaca, 0xacc, 0xad1, 0xad2, 0xad4, 0xad8, 0xae1, 0xae2, 
0xae4, 0xae8, 0xaf0, 0xb07, 0xb0b, 0xb0d, 0xb0e, 0xb13, 0xb15, 0xb16, 0xb19, 0xb1a, 0xb1c, 0xb23, 0xb25, 0xb26, 
0xb29, 0xb2a, 0xb2c, 0xb31, 0xb32, 0xb34, 0xb38, 0xb43, 0xb45, 0xb46, 0xb49, 0xb4a, 0xb4c, 0xb51, 0xb52, 0xb54, 
0xb58, 0xb61, 0xb62, 0xb64, 0xb68, 0xb70, 0xb83, 0xb85, 0xb86, 0xb89, 0xb8a, 0xb8c, 0xb91, 0xb92, 0xb94, 0xb98, 
0xba1, 0xba2, 0xba4, 0xba8, 0xbb0, 0xbc1, 0xbc2, 0xbc4, 0xbc8, 0xbd0, 0xbe0, 0xc0f, 0xc17, 0xc1b, 0xc1d, 0xc1e, 
0xc27, 0xc2b, 0xc2d, 0xc2e, 0xc33, 0xc35, 0xc36, 0xc39, 0xc3a, 0xc3c, 0xc47, 0xc4b, 0xc4d, 0xc4e, 0xc53, 0xc55, 
0xc56, 0xc59, 0xc5a, 0xc5c, 0xc63, 0xc65, 0xc66, 0xc69, 0xc6a, 0xc6c, 0xc71, 0xc72, 0xc74, 0xc78, 0xc87, 0xc8b, 
0xc8d, 0xc8e, 0xc93, 0xc95, 0xc96, 0xc99, 0xc9a, 0xc9c, 0xca3, 0xca5, 0xca6, 0xca9, 0xcaa, 0xcac, 0xcb1, 0xcb2, 
0xcb4, 0xcb8, 0xcc3, 0xcc5, 0xcc6, 0xcc9, 0xcca, 0xccc, 0xcd1, 0xcd2, 0xcd4, 0xcd8, 0xce1, 0xce2, 0xce4, 0xce8, 
0xcf0, 0xd07, 0xd0b, 0xd0d, 0xd0e, 0xd13, 0xd15, 0xd16, 0xd19, 0xd1a, 0xd1c, 0xd23, 0xd25, 0xd26, 0xd29, 0xd2a, 
0xd2c, 0xd31, 0xd32, 0xd34, 0xd38, 0xd43, 0xd45, 0xd46, 0xd49, 0xd4a, 0xd4c, 0xd51, 0xd52, 0xd54, 0xd58, 0xd61, 
0xd62, 0xd64, 0xd68, 0xd70, 0xd83, 0xd85, 0xd86, 0xd89, 0xd8a, 0xd8c, 0xd91, 0xd92, 0xd94, 0xd98, 0xda1, 0xda2, 
0xda4, 0xda8, 0xdb0, 0xdc1, 0xdc2, 0xdc4, 0xdc8, 0xdd0, 0xde0, 0xe07, 0xe0b, 0xe0d, 0xe0e, 0xe13, 0xe15, 0xe16, 
0xe19, 0xe1a, 0xe1c, 0xe23, 0xe25, 0xe26, 0xe29, 0xe2a, 0xe2c, 0xe31, 0xe32, 0xe34, 0xe38, 0xe43, 0xe45, 0xe46, 
0xe49, 0xe4a, 0xe4c, 0xe51, 0xe52, 0xe54, 0xe58, 0xe61, 0xe62, 0xe64, 0xe68, 0xe70, 0xe83, 0xe85, 0xe86, 0xe89, 
0xe8a, 0xe8c, 0xe91, 0xe92, 0xe94, 0xe98, 0xea1, 0xea2, 0xea4, 0xea8, 0xeb0, 0xec1, 0xec2, 0xec4, 0xec8, 0xed0, 
0xee0, 0xf03, 0xf05, 0xf06, 0xf09, 0xf0a, 0xf0c, 0xf11, 0xf12, 0xf14, 0xf18, 0xf21, 0xf22, 0xf24, 0xf28, 0xf30, 
0xf41, 0xf42, 0xf44, 0xf48, 0xf50, 0xf60, 0xf81, 0xf82, 0xf84, 0xf88, 0xf90, 0xfa0, 0xfc0, 0x07f, 0x0bf, 0x0df, 
0x0ef, 0x0f7, 0x0fb, 0x0fd, 0x0fe, 0x13f, 0x15f, 0x16f, 0x177, 0x17b, 0x17d, 0x17e, 0x19f, 0x1af, 0x1b7, 0x1bb, 
0x1bd, 0x1be, 0x1cf, 0x1d7, 0x1db, 0x1dd, 0x1de, 0x1e7, 0x1eb, 0x1ed, 0x1ee, 0x1f3, 0x1f5, 0x1f6, 0x1f9, 0x1fa, 
0x1fc, 0x23f, 0x25f, 0x26f, 0x277, 0x27b, 0x27d, 0x27e, 0x29f, 0x2af, 0x2b7, 0x2bb, 0x2bd, 0x2be, 0x2cf, 0x2d7, 
0x2db, 0x2dd, 0x2de, 0x2e7, 0x2eb, 0x2ed, 0x2ee, 0x2f3, 0x2f5, 0x2f6, 0x2f9, 0x2fa, 0x2fc, 0x31f, 0x32f, 0x337, 
0x33b, 0x33d, 0x33e, 0x34f, 0x357, 0x35b, 0x35d, 0x35e, 0x367, 0x36b, 0x36d, 0x36e, 0x373, 0x375, 0x376, 0x379, 
0x37a, 0x37c, 0x38f, 0x397, 0x39b, 0x39d, 0x39e, 0x3a7, 0x3ab, 0x3ad, 0x3ae, 0x3b3, 0x3b5, 0x3b6, 0x3b9, 0x3ba, 
0x3bc, 0x3c7, 0x3cb, 0x3cd, 0x3ce, 0x3d3, 0x3d5, 0x3d6, 0x3d9, 0x3da, 0x3dc, 0x3e3, 0x3e5, 0x3e6, 0x3e9, 0x3ea, 
0x3ec, 0x3f1, 0x3f2, 0x3f4, 0x3f8, 0x43f, 0x45f, 0x46f, 0x477, 0x47b, 0x47d, 0x47e, 0x49f, 0x4af, 0x4b7, 0x4bb, 
0x4bd, 0x4be, 0x4cf, 0x4d7, 0x4db, 0x4dd, 0x4de, 0x4e7, 0x4eb, 0x4ed, 0x4ee, 0x4f3, 0x4f5, 0x4f6, 0x4f9, 0x4fa, 
0x4fc, 0x51f, 0x52f, 0x537, 0x53b, 0x53d, 0x53e, 0x54f, 0x557, 0x55b, 0x55d, 0x55e, 0x567, 0x56b, 0x56d, 0x56e, 
0x573, 0x575, 0x576, 0x579, 0x57a, 0x57c, 0x58f, 0x597, 0x59b, 0x59d, 0x59e, 0x5a7, 0x5ab, 0x5ad, 0x5ae, 0x5b3, 
0x5b5, 0x5b6, 0x5b9, 0x5ba, 0x5bc, 0x5c7, 0x5cb, 0x5cd, 0x5ce, 0x5d3, 0x5d5, 0x5d6, 0x5d9, 0x5da, 0x5dc, 0x5e3, 
0x5e5, 0x5e6, 0x5e9, 0x5ea, 0x5ec, 0x5f1, 0x5f2, 0x5f4, 0x5f8, 0x61f, 0x62f, 0x637, 0x63b, 0x63d, 0x63e, 0x64f, 
0x657, 0x65b, 0x65d, 0x65e, 0x667, 0x66b, 0x66d, 0x66e, 0x673, 0x675, 0x676, 0x679, 0x67a, 0x67c, 0x68f, 0x697, 
0x69b, 0x69d, 0x69e, 0x6a7, 0x6ab, 0x6ad, 0x6ae, 0x6b3, 0x6b5, 0x6b6, 0x6b9, 0x6ba, 0x6bc, 0x6c7, 0x6cb, 0x6cd, 
0x6ce, 0x6d3, 0x6d5, 0x6d6, 0x6d9, 0x6da, 0x6dc, 0x6e3, 0x6e5, 0x6e6, 0x6e9, 0x6ea, 0x6ec, 0x6f1, 0x6f2, 0x6f4, 
0x6f8, 0x70f, 0x717, 0x71b, 0x71d, 0x71e, 0x727, 0x72b, 0x72d, 0x72e, 0x733, 0x735, 0x736, 0x739, 0x73a, 0x73c, 
0x747, 0x74b, 0x74d, 0x74e, 0x753, 0x755, 0x756, 0x759, 0x75a, 0x75c, 0x763, 0x765, 0x766, 0x769, 0x76a, 0x76c, 
0x771, 0x772, 0x774, 0x778, 0x787, 0x78b, 0x78d, 0x78e, 0x793, 0x795, 0x796, 0x799, 0x79a, 0x79c, 0x7a3, 0x7a5, 
0x7a6, 0x7a9, 0x7aa, 0x7ac, 0x7b1, 0x7b2, 0x7b4, 0x7b8, 0x7c3, 0x7c5, 0x7c6, 0x7c9, 0x7ca, 0x7cc, 0x7d1, 0x7d2, 
0x7d4, 0x7d8, 0x7e1, 0x7e2, 0x7e4, 0x7e8, 0x7f0, 0x83f, 0x85f, 0x86f, 0x877, 0x87b, 0x87d, 0x87e, 0x89f, 0x8af, 
0x8b7, 0x8bb, 0x8bd, 0x8be, 0x8cf, 0x8d7, 0x8db, 0x8dd, 0x8de, 0x8e7, 0x8eb, 0x8ed, 0x8ee, 0x8f3, 0x8f5, 0x8f6, 
0x8f9, 0x8fa, 0x8fc, 0x91f, 0x92f, 0x937, 0x93b, 0x93d, 0x93e, 0x94f, 0x957, 0x95b, 0x95d, 0x95e, 0x967, 0x96b, 
0x96d, 0x96e, 0x973, 0x975, 0x976, 0x979, 0x97a, 0x97c, 0x98f, 0x997, 0x99b, 0x99d, 0x99e, 0x9a7, 0x9ab, 0x9ad, 
0x9ae, 0x9b3, 0x9b5, 0x9b6, 0x9b9, 0x9ba, 0x9bc, 0x9c7, 0x9cb, 0x9cd, 0x9ce, 0x9d3, 0x9d5, 0x9d6, 0x9d9, 0x9da, 
0x9dc, 0x9e3, 0x9e5, 0x9e6, 0x9e9, 0x9ea, 0x9ec, 0x9f1, 0x9f2, 0x9f4, 0x9f8, 0xa1f, 0xa2f, 0xa37, 0xa3b, 0xa3d, 
0xa3e, 0xa4f, 0xa57, 0xa5b, 0xa5d, 0xa5e, 0xa67, 0xa6b, 0xa6d, 0xa6e, 0xa73, 0xa75, 0xa76, 0xa79, 0xa7a, 0xa7c, 
0xa8f, 0xa97, 0xa9b, 0xa9d, 0xa9e, 0xaa7, 0xaab, 0xaad, 0xaae, 0xab3, 0xab5, 0xab6, 0xab9, 0xaba, 0xabc, 0xac7, 
0xacb, 0xacd, 0xace, 0xad3, 0xad5, 0xad6, 0xad9, 0xada, 0xadc, 0xae3, 0xae5, 0xae6, 0xae9, 0xaea, 0xaec, 0xaf1, 
0xaf2, 0xaf4, 0xaf8, 0xb0f, 0xb17, 0xb1b, 0xb1d, 0xb1e, 0xb27, 0xb2b, 0xb2d, 0xb2e, 0xb33, 0xb35, 0xb36, 0xb39, 
0xb3a, 0xb3c, 0xb47, 0xb4b, 0xb4d, 0xb4e, 0xb53, 0xb55, 0xb56, 0xb59, 0xb5a, 0xb5c, 0xb63, 0xb65, 0xb66, 0xb69, 
0xb6a, 0xb6c, 0xb71, 0xb72, 0xb74, 0xb78, 0xb87, 0xb8b, 0xb8d, 0xb8e, 0xb93, 0xb95, 0xb96, 0xb99, 0xb9a, 0xb9c, 
0xba3, 0xba5, 0xba6, 0xba9, 0xbaa, 0xbac, 0xbb1, 0xbb2, 0xbb4, 0xbb8, 0xbc3, 0xbc5, 0xbc6, 0xbc9, 0xbca, 0xbcc, 
0xbd1, 0xbd2, 0xbd4, 0xbd8, 0xbe1, 0xbe2, 0xbe4, 0xbe8, 0xbf0, 0xc1f, 0xc2f, 0xc37, 0xc3b, 0xc3d, 0xc3e, 0xc4f, 
0xc57, 0xc5b, 0xc5d, 0xc5e, 0xc67, 0xc6b, 0xc6d, 0xc6e, 0xc73, 0xc75, 0xc76, 0xc79, 0xc7a, 0xc7c, 0xc8f, 0xc97, 
0xc9b, 0xc9d, 0xc9e, 0xca7, 0xcab, 0xcad, 0xcae, 0xcb3, 0xcb5, 0xcb6, 0xcb9, 0xcba, 0xcbc, 0xcc7, 0xccb, 0xccd, 
0xcce, 0xcd3, 0xcd5, 0xcd6, 0xcd9, 0xcda, 0xcdc, 0xce3, 0xce5, 0xce6, 0xce9, 0xcea, 0xcec, 0xcf1, 0xcf2, 0xcf4, 
0xcf8, 0xd0f, 0xd17, 0xd1b, 0xd1d, 0xd1e, 0xd27, 0xd2b, 0xd2d, 0xd2e, 0xd33, 0xd35, 0xd36, 0xd39, 0xd3a, 0xd3c, 
0xd47, 0xd4b, 0xd4d, 0xd4e, 0xd53, 0xd55, 0xd56, 0xd59, 0xd5a, 0xd5c, 0xd63, 0xd65, 0xd66, 0xd69, 0xd6a, 0xd6c, 
0xd71, 0xd72, 0xd74, 0xd78, 0xd87, 0xd8b, 0xd8d, 0xd8e, 0xd93, 0xd95, 0xd96, 0xd99, 0xd9a, 0xd9c, 0xda3, 0xda5, 
0xda6, 0xda9, 0xdaa, 0xdac, 0xdb1, 0xdb2, 0xdb4, 0xdb8, 0xdc3, 0xdc5, 0xdc6, 0xdc9, 0xdca, 0xdcc, 0xdd1, 0xdd2, 
0xdd4, 0xdd8, 0xde1, 0xde2, 0xde4, 0xde8, 0xdf0, 0xe0f, 0xe17, 0xe1b, 0xe1d, 0xe1e, 0xe27, 0xe2b, 0xe2d, 0xe2e, 
0xe33, 0xe35, 0xe36, 0xe39, 0xe3a, 0xe3c, 0xe47, 0xe4b, 0xe4d, 0xe4e, 0xe53, 0xe55, 0xe56, 0xe59, 0xe5a, 0xe5c, 
0xe63, 0xe65, 0xe66, 0xe69, 0xe6a, 0xe6c, 0xe71, 0xe72, 0xe74, 0xe78, 0xe87, 0xe8b, 0xe8d, 0xe8e, 0xe93, 0xe95, 
0xe96, 0xe99, 0xe9a, 0xe9c, 0xea3, 0xea5, 0xea6, 0xea9, 0xeaa, 0xeac, 0xeb1, 0xeb2, 0xeb4, 0xeb8, 0xec3, 0xec5, 
0xec6, 0xec9, 0xeca, 0xecc, 0xed1, 0xed2, 0xed4, 0xed8, 0xee1, 0xee2, 0xee4, 0xee8, 0xef0, 0xf07, 0xf0b, 0xf0d, 
0xf0e, 0xf13, 0xf15, 0xf16, 0xf19, 0xf1a, 0xf1c, 0xf23, 0xf25, 0xf26, 0xf29, 0xf2a, 0xf2c, 0xf31, 0xf32, 0xf34, 
0xf38, 0xf43, 0xf45, 0xf46, 0xf49, 0xf4a, 0xf4c, 0xf51, 0xf52, 0xf54, 0xf58, 0xf61, 0xf62, 0xf64, 0xf68, 0xf70, 
0xf83, 0xf85, 0xf86, 0xf89, 0xf8a, 0xf8c, 0xf91, 0xf92, 0xf94, 0xf98, 0xfa1, 0xfa2, 0xfa4, 0xfa8, 0xfb0, 0xfc1, 
0xfc2, 0xfc4, 0xfc8, 0xfd0, 0xfe0, 0x0ff, 0x17f, 0x1bf, 0x1df, 0x1ef, 0x1f7, 0x1fb, 0x1fd, 0x1fe, 0x27f, 0x2bf, 
0x2df, 0x2ef, 0x2f7, 0x2fb, 0x2fd, 0x2fe, 0x33f, 0x35f, 0x36f, 0x377, 0x37b, 0x37d, 0x37e, 0x39f, 0x3af, 0x3b7, 
0x3bb, 0x3bd, 0x3be, 0x3cf, 0x3d7, 0x3db, 0x3dd, 0x3de, 0x3e7, 0x3eb, 0x3ed, 0x3ee, 0x3f3, 0x3f5, 0x3f6, 0x3f9, 
0x3fa, 0x3fc, 0x47f, 0x4bf, 0x4df, 0x4ef, 0x4f7, 0x4fb, 0x4fd, 0x4fe, 0x53f, 0x55f, 0x56f, 0x577, 0x57b, 0x57d, 
0x57e, 0x59f, 0x5af, 0x5b7, 0x5bb, 0x5bd, 0x5be, 0x5cf, 0x5d7, 0x5db, 0x5dd, 0x5de, 0x5e7, 0x5eb, 0x5ed, 0x5ee, 
0x5f3, 0x5f5, 0x5f6, 0x5f9, 0x5fa, 0x5fc, 0x63f, 0x65f, 0x66f, 0x677, 0x67b, 0x67d, 0x67e, 0x69f, 0x6af, 0x6b7, 
0x6bb, 0x6bd, 0x6be, 0x6cf, 0x6d7, 0x6db, 0x6dd, 0x6de, 0x6e7, 0x6eb, 0x6ed, 0x6ee, 0x6f3, 0x6f5, 0x6f6, 0x6f9, 
0x6fa, 0x6fc, 0x71f, 0x72f, 0x737, 0x73b, 0x73d, 0x73e, 0x74f, 0x757, 0x75b, 0x75d, 0x75e, 0x767, 0x76b, 0x76d, 
0x76e, 0x773, 0x775, 0x776, 0x779, 0x77a, 0x77c, 0x78f, 0x797, 0x79b, 0x79d, 0x79e, 0x7a7, 0x7ab, 0x7ad, 0x7ae, 
0x7b3, 0x7b5, 0x7b6, 0x7b9, 0x7ba, 0x7bc, 0x7c7, 0x7cb, 0x7cd, 0x7ce, 0x7d3, 0x7d5, 0x7d6, 0x7d9, 0x7da, 0x7dc, 
0x7e3, 0x7e5, 0x7e6, 0x7e9, 0x7ea, 0x7ec, 0x7f1, 0x7f2, 0x7f4, 0x7f8, 0x87f, 0x8bf, 0x8df, 0x8ef, 0x8f7, 0x8fb, 
0x8fd, 0x8fe, 0x93f, 0x95f, 0x96f, 0x977, 0x97b, 0x97d, 0x97e, 0x99f, 0x9af, 0x9b7, 0x9bb, 0x9bd, 0x9be, 0x9cf, 
0x9d7, 0x9db, 0x9dd, 0x9de, 0x9e7, 0x9eb, 0x9ed, 0x9ee, 0x9f3, 0x9f5, 0x9f6, 0x9f9, 0x9fa, 0x9fc, 0xa3f, 0xa5f, 
0xa6f, 0xa77, 0xa7b, 0xa7d, 0xa7e, 0xa9f, 0xaaf, 0xab7, 0xabb, 0xabd, 0xabe, 0xacf, 0xad7, 0xadb, 0xadd, 0xade, 
0xae7, 0xaeb, 0xaed, 0xaee, 0xaf3, 0xaf5, 0xaf6, 0xaf9, 0xafa, 0xafc, 0xb1f, 0xb2f, 0xb37, 0xb3b, 0xb3d, 0xb3e, 
0xb4f, 0xb57, 0xb5b, 0xb5d, 0xb5e, 0xb67, 0xb6b, 0xb6d, 0xb6e, 0xb73, 0xb75, 0xb76, 0xb79, 0xb7a, 0xb7c, 0xb8f, 
0xb97, 0xb9b, 0xb9d, 0xb9e, 0xba7, 0xbab, 0xbad, 0xbae, 0xbb3, 0xbb5, 0xbb6, 0xbb9, 0xbba, 0xbbc, 0xbc7, 0xbcb, 
0xbcd, 0xbce, 0xbd3, 0xbd5, 0xbd6, 0xbd9, 0xbda, 0xbdc, 0xbe3, 0xbe5, 0xbe6, 0xbe9, 0xbea, 0xbec, 0xbf1, 0xbf2, 
0xbf4, 0xbf8, 0xc3f, 0xc5f, 0xc6f, 0xc77, 0xc7b, 0xc7d, 0xc7e, 0xc9f, 0xcaf, 0xcb7, 0xcbb, 0xcbd, 0xcbe, 0xccf, 
0xcd7, 0xcdb, 0xcdd, 0xcde, 0xce7, 0xceb, 0xced, 0xcee, 0xcf3, 0xcf5, 0xcf6, 0xcf9, 0xcfa, 0xcfc, 0xd1f, 0xd2f, 
0xd37, 0xd3b, 0xd3d, 0xd3e, 0xd4f, 0xd57, 0xd5b, 0xd5d, 0xd5e, 0xd67, 0xd6b, 0xd6d, 0xd6e, 0xd73, 0xd75, 0xd76, 
0xd79, 0xd7a, 0xd7c, 0xd8f, 0xd97, 0xd9b, 0xd9d, 0xd9e, 0xda7, 0xdab, 0xdad, 0xdae, 0xdb3, 0xdb5, 0xdb6, 0xdb9, 
0xdba, 0xdbc, 0xdc7, 0xdcb, 0xdcd, 0xdce, 0xdd3, 0xdd5, 0xdd6, 0xdd9, 0xdda, 0xddc, 0xde3, 0xde5, 0xde6, 0xde9, 
0xdea, 0xdec, 0xdf1, 0xdf2, 0xdf4, 0xdf8, 0xe1f, 0xe2f, 0xe37, 0xe3b, 0xe3d, 0xe3e, 0xe4f, 0xe57, 0xe5b, 0xe5d, 
0xe5e, 0xe67, 0xe6b, 0xe6d, 0xe6e, 0xe73, 0xe75, 0xe76, 0xe79, 0xe7a, 0xe7c, 0xe8f, 0xe97, 0xe9b, 0xe9d, 0xe9e, 
0xea7, 0xeab, 0xead, 0xeae, 0xeb3, 0xeb5, 0xeb6, 0xeb9, 0xeba, 0xebc, 0xec7, 0xecb, 0xecd, 0xece, 0xed3, 0xed5, 
0xed6, 0xed9, 0xeda, 0xedc, 0xee3, 0xee5, 0xee6, 0xee9, 0xeea, 0xeec, 0xef1, 0xef2, 0xef4, 0xef8, 0xf0f, 0xf17, 
0xf1b, 0xf1d, 0xf1e, 0xf27, 0xf2b, 0xf2d, 0xf2e, 0xf33, 0xf35, 0xf36, 0xf39, 0xf3a, 0xf3c, 0xf47, 0xf4b, 0xf4d, 
0xf4e, 0xf53, 0xf55, 0xf56, 0xf59, 0xf5a, 0xf5c, 0xf63, 0xf65, 0xf66, 0xf69, 0xf6a, 0xf6c, 0xf71, 0xf72, 0xf74, 
0xf78, 0xf87, 0xf8b, 0xf8d, 0xf8e, 0xf93, 0xf95, 0xf96, 0xf99, 0xf9a, 0xf9c, 0xfa3, 0xfa5, 0xfa6, 0xfa9, 0xfaa, 
0xfac, 0xfb1, 0xfb2, 0xfb4, 0xfb8, 0xfc3, 0xfc5, 0xfc6, 0xfc9, 0xfca, 0xfcc, 0xfd1, 0xfd2, 0xfd4, 0xfd8, 0xfe1, 
0xfe2, 0xfe4, 0xfe8, 0xff0, 0x1ff, 0x2ff, 0x37f, 0x3bf, 0x3df, 0x3ef, 0x3f7, 0x3fb, 0x3fd, 0x3fe, 0x4ff, 0x57f, 
0x5bf, 0x5df, 0x5ef, 0x5f7, 0x5fb, 0x5fd, 0x5fe, 0x67f, 0x6bf, 0x6df, 0x6ef, 0x6f7, 0x6fb, 0x6fd, 0x6fe, 0x73f, 
0x75f, 0x76f, 0x777, 0x77b, 0x77d, 0x77e, 0x79f, 0x7af, 0x7b7, 0x7bb, 0x7bd, 0x7be, 0x7cf, 0x7d7, 0x7db, 0x7dd, 
0x7de, 0x7e7, 0x7eb, 0x7ed, 0x7ee, 0x7f3, 0x7f5, 0x7f6, 0x7f9, 0x7fa, 0x7fc, 0x8ff, 0x97f, 0x9bf, 0x9df, 0x9ef, 
0x9f7, 0x9fb, 0x9fd, 0x9fe, 0xa7f, 0xabf, 0xadf, 0xaef, 0xaf7, 0xafb, 0xafd, 0xafe, 0xb3f, 0xb5f, 0xb6f, 0xb77, 
0xb7b, 0xb7d, 0xb7e, 0xb9f, 0xbaf, 0xbb7, 0xbbb, 0xbbd, 0xbbe, 0xbcf, 0xbd7, 0xbdb, 0xbdd, 0xbde, 0xbe7, 0xbeb, 
0xbed, 0xbee, 0xbf3, 0xbf5, 0xbf6, 0xbf9, 0xbfa, 0xbfc, 0xc7f, 0xcbf, 0xcdf, 0xcef, 0xcf7, 0xcfb, 0xcfd, 0xcfe, 
0xd3f, 0xd5f, 0xd6f, 0xd77, 0xd7b, 0xd7d, 0xd7e, 0xd9f, 0xdaf, 0xdb7, 0xdbb, 0xdbd, 0xdbe, 0xdcf, 0xdd7, 0xddb, 
0xddd, 0xdde, 0xde7, 0xdeb, 0xded, 0xdee, 0xdf3, 0xdf5, 0xdf6, 0xdf9, 0xdfa, 0xdfc, 0xe3f, 0xe5f, 0xe6f, 0xe77, 
0xe7b, 0xe7d, 0xe7e, 0xe9f, 0xeaf, 0xeb7, 0xebb, 0xebd, 0xebe, 0xecf, 0xed7, 0xedb, 0xedd, 0xede, 0xee7, 0xeeb, 
0xeed, 0xeee, 0xef3, 0xef5, 0xef6, 0xef9, 0xefa, 0xefc, 0xf1f, 0xf2f, 0xf37, 0xf3b, 0xf3d, 0xf3e, 0xf4f, 0xf57, 
0xf5b, 0xf5d, 0xf5e, 0xf67, 0xf6b, 0xf6d, 0xf6e, 0xf73, 0xf75, 0xf76, 0xf79, 0xf7a, 0xf7c, 0xf8f, 0xf97, 0xf9b, 
0xf9d, 0xf9e, 0xfa7, 0xfab, 0xfad, 0xfae, 0xfb3, 0xfb5, 0xfb6, 0xfb9, 0xfba, 0xfbc, 0xfc7, 0xfcb, 0xfcd, 0xfce, 
0xfd3, 0xfd5, 0xfd6, 0xfd9, 0xfda, 0xfdc, 0xfe3, 0xfe5, 0xfe6, 0xfe9, 0xfea, 0xfec, 0xff1, 0xff2, 0xff4, 0xff8, 
0x3ff, 0x5ff, 0x6ff, 0x77f, 0x7bf, 0x7df, 0x7ef, 0x7f7, 0x7fb, 0x7fd, 0x7fe, 0x9ff, 0xaff, 0xb7f, 0xbbf, 0xbdf, 
0xbef, 0xbf7, 0xbfb, 0xbfd, 0xbfe, 0xcff, 0xd7f, 0xdbf, 0xddf, 0xdef, 0xdf7, 0xdfb, 0xdfd, 0xdfe, 0xe7f, 0xebf, 
0xedf, 0xeef, 0xef7, 0xefb, 0xefd, 0xefe, 0xf3f, 0xf5f, 0xf6f, 0xf77, 0xf7b, 0xf7d, 0xf7e, 0xf9f, 0xfaf, 0xfb7, 
0xfbb, 0xfbd, 0xfbe, 0xfcf, 0xfd7, 0xfdb, 0xfdd, 0xfde, 0xfe7, 0xfeb, 0xfed, 0xfee, 0xff3, 0xff5, 0xff6, 0xff9, 
0xffa, 0xffc, 0x7ff, 0xbff, 0xdff, 0xeff, 0xf7f, 0xfbf, 0xfdf, 0xfef, 0xff7, 0xffb, 0xffd, 0xffe, 0xfff, 
};
