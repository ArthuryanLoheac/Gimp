#include <criterion/criterion.h>
#include "App/Popup/PopupFolder.hpp"

Test(PopupFolder, basic_init) {
    MyGimp::PopupFolder popup;
    cr_assert(true); // Construction ne doit pas crasher
}

Test(PopupFolder, extension_utils) {
    MyGimp::PopupFolder popup;
    std::vector<std::string> exts = {".png", ".jpg", ".jpeg"};
    popup.setExtensions(exts);
    std::string ext = popup.getExtension("image.jpeg");
    cr_assert(ext == ".jpeg");
}

Test(PopupFolder, get_extension) {
    MyGimp::PopupFolder popup;
    std::string ext1 = popup.getExtension("photo.png");
    std::string ext2 = popup.getExtension("document.pdf");
    std::string ext3 = popup.getExtension("archive");
    cr_assert(ext1 == ".png");
    cr_assert(ext2 == ".pdf");
    cr_assert(ext3 == "");
}

Test (PopupFolder, set_extensions) {
    MyGimp::PopupFolder popup;
    std::vector<std::string> exts = {".png", ".jpg", ".jpeg"};
    popup.setExtensions(exts);
    cr_assert(popup.isGoodExtension("photo.png"));
    cr_assert(!popup.isGoodExtension("photo.bmp"));
}
