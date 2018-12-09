unsigned int    color1(int i)
{
    return ((i % 256) << 16 | (i * i % 256) << 8 | (255 - i) % 256);
}

unsigned int    color2(int i)
{
    return ((i % 256) << 8 | (i * i % 256) | (255 - i) % 256 << 16);
}

unsigned int    color3(int i)
{
    return ((i % 256) | (i * i % 256) << 16 | (255 - i) % 256 << 8);
}