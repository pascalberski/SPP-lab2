#include "test.h"

#include "image/bitmap_image.h"

class BitmapTest : public LabTest {};

TEST_F(BitmapTest, test_one_b_one) {
    ASSERT_THROW(auto val = BitmapImage(0, 0), std::exception);
    ASSERT_THROW(auto val = BitmapImage(1'024'001, 0), std::exception);
    ASSERT_THROW(auto val = BitmapImage(0, 1'024'001), std::exception);

    ASSERT_NO_THROW(auto val = BitmapImage(1, 1));
    ASSERT_NO_THROW(auto val = BitmapImage(1'024'000, 1'024'000));

    auto bpi = BitmapImage(1'024'000, 1'024'000);
    ASSERT_THROW(auto val = bpi.get_pixel(0, 1'024'000), std::exception);
    ASSERT_THROW(auto val = bpi.get_pixel(1'024'000, 0), std::exception);
    ASSERT_THROW(bpi.set_pixel(0, 1'024'000, BitmapImage::BitmapPixel{}), std::exception);
    ASSERT_THROW(bpi.set_pixel(1'024'000, 0, BitmapImage::BitmapPixel{}), std::exception);

    ASSERT_NO_THROW(auto val = bpi.get_pixel(0, 1'023'999));
    ASSERT_NO_THROW(auto val = bpi.get_pixel(1'023'999, 0));
    ASSERT_NO_THROW(bpi.set_pixel(0, 1'023'999, BitmapImage::BitmapPixel{}));
    ASSERT_NO_THROW(bpi.set_pixel(1'023'999, 0, BitmapImage::BitmapPixel{}));
}
