#include "level.hpp"
#include "display.hpp"

constexpr Color kRed       = {255, 0, 0};
constexpr Color kBlue      = {0, 0, 255};
constexpr Color kTurquoise = {0, 255, 255};

constexpr uint16_t kMaxDelta = to_millis_scaled(4000);

Level::Level(const uint8_t *source, uint16_t len)
    : source_(source)
    , bits_left_(len * 8)
{
    for (uint8_t i = 0; i < blocks_.size(); ++i)
    {
        if (!has_next_block())
            break;
        blocks_.push(load_next_block());
    }
}

void Level::start()
{
    start_time_ = milli_scaled();
}

void Level::update(Display &display, Position pos)
{
    const auto time = elapsed_time();

    display_saber(display, pos);

    for (uint8_t i = 0; i < blocks_.size(); ++i)
    {
        auto &block = blocks_[i];
        if (block.time < time)
        {
            if (has_next_block())
                blocks_.push(load_next_block());
            continue;
        }

        if (block.pos == pos)
            destroy_block(display, block);

        if (static_cast<uint8_t>(block.flags) & static_cast<uint8_t>(BlockFlags::is_destroyed))
            continue;

        // block.time always greater than cur_time
        const auto diff = block.time - time;
        if (diff < kMaxDelta)
            display_block(display, block, diff);
    }
}

uint16_t Level::elapsed_time()
{
    return milli_scaled() - start_time_;
}

uint16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Level::destroy_block(Display &display, Block &block)
{
    block.flags = static_cast<BlockFlags>(static_cast<uint8_t>(block.flags)
                                          | static_cast<uint8_t>(BlockFlags::is_destroyed));

    //const auto start = Position{static_cast<uint8_t>(block.pos.x - 1), static_cast<uint8_t>(block.pos.y - 1)};
    //const auto end   = Position{static_cast<uint8_t>(block.pos.x + 1), static_cast<uint8_t>(block.pos.y + 1)};
    //display.draw_line(start, end, kRed);
}

Color adjust_color(Color c, uint8_t divide)
{
    c.r /= divide;
    c.g /= divide;
    c.b /= divide;
    return c;
}

void Level::display_block(Display &display, Block block, uint16_t dt)
{
    const auto size = static_cast<uint8_t>(map(dt, kMaxDelta, 0, 2, 7));
    const auto div  = static_cast<uint8_t>(map(dt, kMaxDelta, 0, 10, 1));
    const auto fc   = adjust_color(kBlue, div);
    const auto bc   = adjust_color(kTurquoise, div);
    display.draw_cube(block.pos, size, fc, bc);
}

bool Level::pos_approx(Position a, Position b)
{
    return a.x - b.x < Block::radius && a.y - b.y < Block::radius;
}

void Level::display_saber(Display &display, Position pos)
{
    display.fill_rect(display.from_placing(pos), kRed, 4, 4);
}

bool Level::has_next_block()
{
    return bits_left_ >= 21;
}

auto nth_bit(const uint8_t *source, size_t pos) -> uint8_t
{
    const auto byte = pgm_read_byte_near(source + (pos / 8));
    return (byte >> (7 - (pos % 8))) & 1;
}

Block Level::load_next_block()
{
    Block ret{};
    // I know, this cries for refactoring. Lack of time
    ret.time |= nth_bit(source_, bits_offset_ + 0) << 15;
    ret.time |= nth_bit(source_, bits_offset_ + 1) << 14;
    ret.time |= nth_bit(source_, bits_offset_ + 2) << 13;
    ret.time |= nth_bit(source_, bits_offset_ + 3) << 12;
    ret.time |= nth_bit(source_, bits_offset_ + 4) << 11;
    ret.time |= nth_bit(source_, bits_offset_ + 5) << 10;
    ret.time |= nth_bit(source_, bits_offset_ + 6) << 9;
    ret.time |= nth_bit(source_, bits_offset_ + 7) << 8;
    ret.time |= nth_bit(source_, bits_offset_ + 8) << 7;
    ret.time |= nth_bit(source_, bits_offset_ + 9) << 6;
    ret.time |= nth_bit(source_, bits_offset_ + 10) << 5;
    ret.time |= nth_bit(source_, bits_offset_ + 11) << 4;
    ret.time |= nth_bit(source_, bits_offset_ + 12) << 3;
    ret.time |= nth_bit(source_, bits_offset_ + 13) << 2;
    ret.time |= nth_bit(source_, bits_offset_ + 14) << 1;
    ret.time |= nth_bit(source_, bits_offset_ + 15) << 0;

    ret.pos.x = nth_bit(source_, bits_offset_ + 16) << 1;
    ret.pos.x |= nth_bit(source_, bits_offset_ + 17);
    if (ret.pos.x == 3)
        ret.pos.x = 2; // Hardware limit

    ret.pos.y = nth_bit(source_, bits_offset_ + 18) << 1;
    ret.pos.y |= nth_bit(source_, bits_offset_ + 19);

    ret.flags = static_cast<BlockFlags>(nth_bit(source_, bits_offset_ + 20));

    source_ += 2 * sizeof(uint8_t);
    bits_left_ -= 21;
    bits_offset_ += 5;
    if (bits_offset_ >= 8)
    {
        source_ += sizeof(uint8_t);
        bits_offset_ %= 8;
    }

    return ret;
}
