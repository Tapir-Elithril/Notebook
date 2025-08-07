#ifndef _PDADD_H
#define _PDADD_H

class pdaddDiary : public Diary {
public:
    using Diary::Diary;
    ~pdaddDiary() = default;
    void pdadd(string date, vector<string>& content_buffer);
};

class pdaddHandler : public Handler {
private:
    pdaddDiary* pdadddiary;
    void handlepdadd(istringstream& stream) const;
    void handleHelp(istringstream& stream) const override;
public:
    pdaddHandler(pdaddDiary* pdadddiary);
    ~pdaddHandler() = default;
};

#endif 