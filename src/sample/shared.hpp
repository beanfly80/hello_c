// SKIP License...

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(disable : 4819)
#endif

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

namespace sample {

void removeSpace(std::string& s) {
    s.erase(std::remove_if(s.begin(), 
                           s.end(),
                           [](unsigned char x){return std::isspace(x);}),
            s.end());
}

bool setFStream(const char* path,
                const char* data,
                size_t size = 0,
                bool append = false,
                bool isBinary = false) {
    if (!path || !data) {
        assert(false);
        return false;
    }

    if (size == 0)
        size = strlen(data);
    std::ios_base::openmode openMode = std::ios::out; 
    if (append)
        openMode |= std::ios::app;
    if (isBinary) 
        openMode |= std::ios::binary;

    std::ofstream stream(path, openMode);
    if (!stream.is_open()) {
        std::cout << "Cannot save " << path << std::endl;
        assert(false);
        return false;
    }
    stream.write(data, size);
    stream.close();
    return true;
}


class DocFile {
public:
    DocFile(const std::string& epubname, bool addTxt = true) {
        _epubname.assign(epubname).append(".epub");
        if (addTxt)
            _txtname.assign(epubname).append(".txt");
    }
    const char* epubname() { return _epubname.empty() ? nullptr : _epubname.data(); }
    const char* txtname() { return _txtname.empty() ? nullptr : _txtname.data(); }

private:
    std::string _epubname;
    std::string _txtname;
};

class DocTitleList {
public:
    using Docs = std::unordered_map<std::string, std::string>;

    DocTitleList() {}
    void build(const std::string& file) {
        if (!docFiles.empty())
            return;

        assert(!file.empty());
        definedPath = file;
        assert(!definedPath.empty());
        Docs list(ParseDocs(file));
        for (auto& l : list) {
            size_t code = (size_t)std::stoll(l.first, 0, 16);
            docFiles.insert({code, {l.second, (l.second.find("DOC_WEBTOON_") == std::string::npos)}});
        }
    }
    std::unordered_map<size_t, DocFile>& files() { return docFiles; }

private:
    using DocData = std::pair<std::string, std::string>;
    DocData Tokenize(const std::string& str) {
        //#define DOC_FAIRYTALE_CINDERELLA    (DOC_FAIRYTALE | 0x01)  // 신데렐라  0x00100001
        // ->
        // name : DOC_FAIRYTALE_CINDERELLA
        // code : 0x00100001

        size_t name_pos = str.find("DOC_");
        if (name_pos == std::string::npos)
            return DocData();
        // name_pos += 3/*"DOC_"*/;
        std::string name(str.substr(name_pos, str.find("(") - name_pos));
        size_t code_pos = str.rfind("0x");
        if (code_pos == std::string::npos)
            return DocData();

        std::string code(str.substr(code_pos));

        removeSpace(code);
        removeSpace(name);
        return {code, name};
    }

    Docs ParseDocs(const std::string& path) {
        Docs doclist;
        std::ifstream file(path);
        if (!file.is_open()) {
            assert(false);
            return doclist;
        }

        std::string buffer;
        while (!file.eof()) {
            std::getline(file, buffer);

            if (buffer.find("#define DOC_") == std::string::npos ||
                buffer.find("_INDEX") != std::string::npos ||
                buffer.find("DOC_KIND_") != std::string::npos)
                continue;

            if (buffer.find("| 0x") == std::string::npos) {
                continue;
            }

            doclist.insert(Tokenize(buffer)); // ("0x00100001", "DOC_FAIRYTALE_CINDERELLA")
            buffer.clear();
        }
        return doclist;
    }

private:
    std::string definedPath;
    std::unordered_map<size_t, DocFile> docFiles;
};
}