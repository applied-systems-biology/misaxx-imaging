#include <misaxx-imaging/patterns/misa_image_pattern.h>

using namespace misaxx;
using namespace misaxx_imaging;

misa_image_pattern::misa_image_pattern() : misa_file_pattern({ ".tif", ".tiff", ".png",
                                                                         ".bmp", ".pbm", ".pgm",
                                                                         ".ppm", ".jpeg", ".jpg",
                                                                         ".jpe", ".jp2" }) {

}

void misa_image_pattern::build_serialization_id_hierarchy(std::vector<misa_serialization_id> &result) const {
    misa_file_pattern::build_serialization_id_hierarchy(result);
    result.emplace_back(misa_serialization_id("misa-imaging", "patterns/image-file"));
}
