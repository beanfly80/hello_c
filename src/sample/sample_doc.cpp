// SKIP License...

/*
    How to work this sample :
    1. Read file sample_doc_title.h
    2. Find a title & code of documents in the file.
    3. Make document files in the out/ directory.

    result)
    (000) "DOC_ART_PICASO.epub"
    (001) "DOC_ART_PICASO.txt"
    (002) "DOC_FAIRYTALE_ALICE.epub"
    (003) "DOC_FAIRYTALE_ALICE.txt"
    (004) "DOC_FAIRYTALE_CINDERELLA.epub"
    (005) "DOC_FAIRYTALE_CINDERELLA.txt"
    (006) "DOC_FAIRYTALE_THREE_LITTLE_PIGS.epub"
    (007) "DOC_FAIRYTALE_THREE_LITTLE_PIGS.txt"
    (008) "DOC_NOVEL_BOY_COMES.epub"
    (009) "DOC_NOVEL_BOY_COMES.txt"
    (010) "DOC_WEBTOON_LEVEL_UP.epub"
    (011) "DOC_WEBTOON_YUMIS_CELLS.epub"
*/

#include <filesystem>
#include "shared.hpp"

#define ENABLE_GTEST
#ifdef ENABLE_GTEST
#include <gtest/gtest.h>
#endif

std::filesystem::path outDir("out/");

void makeDocFilesUsingFileName() {
    sample::DocTitleList titleList;

    titleList.build("sample_doc_title.h");

    for (auto& result : titleList.files()) {
        std::string docID(std::to_string(result.first));
    
        std::string fullPathEpub{outDir.string() + result.second.epubname()};
        sample::setFStream(fullPathEpub.data(), docID.data());
        if (!result.second.txtname())
            continue;

        std::string fullPathTxt{outDir.string() + result.second.txtname()};
        sample::setFStream(fullPathTxt.data(), docID.data());
    }
}

void displayDescription() {
#ifdef ____HELLO_SAMPLE_PARAGRAPH____
    #error "____HELLO_SAMPLE_PARAGRAPH____ is aleady defined!"
#else
    #define ____HELLO_SAMPLE_PARAGRAPH____(s) std::cout << (s) << std::endl;
#endif
    ____HELLO_SAMPLE_PARAGRAPH____("How to work this sample :")
    ____HELLO_SAMPLE_PARAGRAPH____("1. Read sample_doc_title.h")
    ____HELLO_SAMPLE_PARAGRAPH____("2. Find a title & code of documents in the file.")
    ____HELLO_SAMPLE_PARAGRAPH____("3. Make document files in the ")
    ____HELLO_SAMPLE_PARAGRAPH____(" ========================================= ")
    ____HELLO_SAMPLE_PARAGRAPH____(std::filesystem::absolute(outDir).string().c_str());
    ____HELLO_SAMPLE_PARAGRAPH____("")
#undef ____HELLO_SAMPLE_PARAGRAPH
}


std::vector<std::string> verify_result() {
    std::vector<std::string> files;
    for (const auto& f : std::filesystem::directory_iterator(outDir)) {
        files.push_back(f.path().filename().string());
    }
    return files;
}

TEST(testcase_sample, test_filelist)
{
    std::vector<std::string> files;
    EXPECT_NE(verify_result(), files);

    files = {
        "DOC_ART_PICASO.epub",
        "DOC_ART_PICASO.txt",
        "DOC_FAIRYTALE_ALICE.epub",
        "DOC_FAIRYTALE_ALICE.txt",
        "DOC_FAIRYTALE_CINDERELLA.epub",
        "DOC_FAIRYTALE_CINDERELLA.txt",
        "DOC_FAIRYTALE_THREE_LITTLE_PIGS.epub",
        "DOC_FAIRYTALE_THREE_LITTLE_PIGS.txt",
        "DOC_NOVEL_BOY_COMES.epub",
        "DOC_NOVEL_BOY_COMES.txt",
        "DOC_WEBTOON_LEVEL_UP.epub",
        "DOC_WEBTOON_YUMIS_CELLS.epub"
    };
    EXPECT_EQ(verify_result(), files);
}

void result() {
    std::cout << "result) " << std::endl;
    int index = 0;

    for (const auto& f : std::filesystem::directory_iterator(outDir))
        std::cout << "(" << std::setfill('0') << std::setw(3) << index++ << ") " << f.path().filename() << std::endl;

    if (index == 0)
        std::cout << "Empty." << std::endl;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    displayDescription();

    outDir.make_preferred();
    std::filesystem::remove_all(outDir);
    std::filesystem::create_directories(outDir);
    
    makeDocFilesUsingFileName();
    result();

    return RUN_ALL_TESTS();
}