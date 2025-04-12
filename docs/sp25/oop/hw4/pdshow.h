#ifndef _PDSHOW_H
#define _PDSHOW_H

class pdshowDiary : public Diary {
public:
    using Diary::Diary;
    ~pdshowDiary() = default;
    void pdshow(string date);
};

class pdshowHandler : public Handler {
private:
    pdshowDiary* pdshowdiary;
    void handlepdshow(istringstream& stream) const;
    void handleHelp(istringstream& stream) const override;
public:
    pdshowHandler(pdshowDiary* pdshowdiary);
    ~pdshowHandler() = default;
};

#endif 