#ifndef _PDLIST_H
#define _PDLIST_H

class pdlistDiary : public Diary {
    public:
        using Diary::Diary;
        ~pdlistDiary() = default;
        void pdlist();
        void pdlist(string start_date,string end_date);
    };
    
class pdlistHandler : public Handler {
private:
    pdlistDiary* pdlistdiary;
    void handlepdlist(istringstream& stream) const;
    void handleHelp(istringstream& stream) const override;
public:
    pdlistHandler(pdlistDiary* pdlistdiary);
    ~pdlistHandler() = default;
};
    

#endif