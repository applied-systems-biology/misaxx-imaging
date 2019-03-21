#include <misaxx/imaging/caches/misa_image_stack_cache.h>

void
misaxx::imaging::misa_image_stack_cache::do_link(const misaxx::imaging::misa_image_stack_description &t_description) {
    auto &files = this->get();
    for(const auto &kv : t_description.files) {
        misa_image_description description;
        description.filename = kv.second.filename;
        misa_image_file cache;
        cache.suggest_link(this->get_internal_location(), this->get_location(), misaxx::misa_description_storage::with(std::move(description))); // We link manually with the loaded description
        files.insert({ kv.first, cache });
    }

    this->set_unique_location(this->get_location());
}

misaxx::imaging::misa_image_stack_description
misaxx::imaging::misa_image_stack_cache::produce_description(const boost::filesystem::path &t_location,
                                                             const misaxx::imaging::misa_image_stack_pattern &t_pattern) {
    misa_image_stack_description result;
    t_pattern.apply(result, t_location);
    return result;
}
