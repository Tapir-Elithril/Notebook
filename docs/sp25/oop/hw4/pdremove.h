#ifndef _PDREMOVE_H
#define _PDREMOVE_H

class pdremoveDiary : public Diary {
public:
    using Diary::Diary;
    ~pdremoveDiary() = default;
    int pdremove(string date);
};

class pdremoveHandler : public Handler {
private:
    pdremoveDiary* pdremovediary;
    void handlepdremove(istringstream& stream) const;
    void handleHelp(istringstream& stream) const override;
public:
    pdremoveHandler(pdremoveDiary* pdremovediary);
    ~pdremoveHandler() = default;
};

#endif