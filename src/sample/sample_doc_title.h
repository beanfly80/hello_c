// SKIP License...
// Test data for sample_doc

#define DOC_FAIRYTALE 0x00100000  // 동화책
#define DOC_FAIRYTALE_INDEX 0
#define DOC_FAIRYTALE_CINDERELLA	            (DOC_FAIRYTALE | 0x01)  // 신데렐라  0x00100001
#define DOC_FAIRYTALE_ALICE                     (DOC_FAIRYTALE | 0x02)  // 이상한 나라의 앨리스  0x00100002
#define DOC_FAIRYTALE_THREE_LITTLE_PIGS         (DOC_FAIRYTALE | 0x03)  // 아기 돼지 삼형제  0x00100003

#define DOC_WEBTOON 0x01000000  // 웹툰
#define DOC_WEBTOON_INDEX 1
#define DOC_WEBTOON_LEVEL_UP                    (DOC_WEBTOON | 0x01)  // 나 혼자만 레벨업  0x01000001
#define DOC_WEBTOON_YUMIS_CELLS                 (DOC_WEBTOON | 0x02)  // 유미의세포들  0x01000002

#define TEST_UGLY_DATA
#define TEST_UGLY_DATA2 "abc"

#define DOC_NOVEL 0x01200000  // 소설
#define DOC_NOVEL_INDEX 2
#define DOC_NOVEL_BOY_COMES                     (DOC_NOVEL | 0x01)  // 소년이 온다  0x01200001

#define DOC_ART 0x01300000  // 예술
#define DOC_ART_INDEX 3
#define DOC_ART_PICASO                          (DOC_ART | 0x01)  // 위대한 예술가 피카소  0x01300001

#define DOC_KIND_INDEX_LAST     (DOC_ART_INDEX)
#define DOC_KIND_TOTAL          (DOC_KIND_INDEX_LAST+1)

// EOF