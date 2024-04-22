#pragma once
#include "../../Common.h"

constexpr int FIELD_SIZE_W = 14;
constexpr int FIELD_SIZE_H = 22;

constexpr int MINO_SIZE_W = 4;
constexpr int MINO_SIZE_H = 4;

constexpr int MINO_DEFAULT_POS_X = 5;
constexpr int MINO_DEFAULT_POS_Y = 0;

constexpr int NEXT_MINO_NUM = 3;

constexpr int NEXT_MINO_POS_X = 1000;
constexpr int NEXT_MINO_POS_Y = 100;
constexpr int NEXT_MINO_OFFSET = 100;

constexpr int MOVE_FRAME = 5;
constexpr int ACCELERATION_FRAME = 5;

constexpr int DROP_FRAME = 30;
constexpr int STOP_NUM = 3;

constexpr int DEFAULT_SCORE = 100;

enum class MINO_TYPE
{
    TYPE_NONE = -1,
    TYPE_I,
    TYPE_O,
    TYPE_S,
    TYPE_Z,
    TYPE_J,
    TYPE_L,
    TYPE_T,

    KIND_NUM
};

enum class MINO_ANGLE
{
    ANGLE_0,
    ANGLE_90,
    ANGLE_180,
    ANGLE_270,

    KIND_NUM
};

constexpr int FIELD_POS_X = SCREEN_SIZE_X / 2 - 200;
constexpr int FIELD_POS_Y = 5;

constexpr int BLOCK_IMAGE_SIZE = 32;

constexpr char BLOCK_IMAGE_PATH[(int)MINO_TYPE::KIND_NUM][128] =
{
    "Data/Block/I�u���b�N(32).png",
    "Data/Block/���e�g���X(32).png",
    "Data/Block/S�u���b�N(32).png",
    "Data/Block/Z�u���b�N(32).png",
    "Data/Block/J�u���b�N(32).png",
    "Data/Block/L�u���b�N(32).png",
    "Data/Block/T�u���b�N(32).png",
};

constexpr char MINO_IMAGE_PATH[(int)MINO_TYPE::KIND_NUM][128] =
{
    "Data/Block/I�~�m(16,64).png",
    "Data/Block/O�~�m(32).png",
    "Data/Block/S�~�m(48,32).png",
    "Data/Block/Z�~�m(48,32).png",
    "Data/Block/J�~�m(48,32).png",
    "Data/Block/L�~�m(48,32).png",
    "Data/Block/T�~�m(�� 48,32).png",
};

constexpr char WALL_BLOCK_IMAGE_PATH[128] = "Data/Block/�ǃu���b�N(32).png";

constexpr bool minoShapes[(int)MINO_TYPE::KIND_NUM][(int)MINO_ANGLE::KIND_NUM][MINO_SIZE_H][MINO_SIZE_W] =
{
 // TYPE_I
{
    // ANGLE_0
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0
    },
    // ANGLE_90
    {
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 1,
        0, 0, 0, 0
    },
    // ANGLE_180
    {
        0, 0, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0
    },
    // ANGLE_270
    {
        0, 0, 0, 0,
        1, 1, 1, 1,
        0, 0, 0, 0,
        0, 0, 0, 0
    }
},

// TYPE_O
{
    // ANGLE_0
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_90
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_180
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_270
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    }
},

// TYPE_S
{
    // ANGLE_0
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0
    },
    // ANGLE_90
    {
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_180
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0
    },
    // ANGLE_270
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0
    }
},

// TYPE_Z
{
    // ANGLE_0
    {
        0, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_90
    {
        0, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 1, 0, 0
    },
    // ANGLE_180
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 1,
        0, 0, 0, 0
    },
    // ANGLE_270
    {
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    }
},

// TYPE_J
{
    // ANGLE_0
    {
        0, 0, 1, 0,
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_90
    {
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_180
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0
    },
    // ANGLE_270
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 1,
        0, 0, 0, 0
    }
},

// TYPE_L
{
    // ANGLE_0
    {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_90
    {
        0, 0, 0, 0,
        0, 0, 1, 0,
        1, 1, 1, 0,
        0, 0, 0, 0
    },
    // ANGLE_180
    {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0
    },
    // ANGLE_270
    {
        0, 0, 0, 0,
        0, 1, 1, 1,
        0, 1, 0, 0,
        0, 0, 0, 0
    }
},

// TYPE_T
{
    // ANGLE_0
    {
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    // ANGLE_90
    {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 1, 0, 0
    },
    // ANGLE_180
    {
        0, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 1, 1,
        0, 0, 0, 0
    },
    // ANGLE_270
    {
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0
    }
}
};


