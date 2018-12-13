#ifndef HABERDUYURUCAPS_H
#define HABERDUYURUCAPS_H


#include "containerwidget.h"

class HaberDuyuruCaps : public ContainerWidget
{
public:
    HaberDuyuruCaps(mongocxx::database* _db);


    Signal<std::string> &ClickHaber();
    std::string haberOid() const;
    void setHaberOid(const std::string &haberOid);

    std::string duyuruOid() const;
    void setDuyuruOid(const std::string &duyuruOid);
    Signal<std::string> &ClickDuyuru();

private:
    Signal<std::string> _ClickHaber;
    void emitHaberOid();
    std::string mHaberOid;


    Signal<std::string> _ClickDuyuru;
    void emitDuyuruOid();
    std::string mDuyuruOid;
};



class HaberDuyuruCapsItem : public ContainerWidget
{
public:
    HaberDuyuruCapsItem(mongocxx::database* _db , bool m_Haber = false );


    std::string haberTitle() const;
    void setHaberTitle(const std::string &haberTitle);

    std::string backGroundImg() const;
    void setBackGroundImg(const std::string &backGroundImg);

    std::string haberOid() const;
    void setHaberOid(const std::string &haberOid);

    std::string duyuruTipi() const;
    void setDuyuruTipi(const std::string &duyuruTipi);

    std::string duyuruBaslik() const;
    void setDuyuruBaslik(const std::string &duyuruBaslik);

    std::string duyuruOid() const;
    void setDuyuruOid(const std::string &duyuruOid);

private:
    void loadHaber();

    void loadDuyuru();


    std::string mHaberTitle;
    std::string mBackGroundImg;
    std::string mHaberOid;


    std::string mDuyuruTipi;
    std::string mDuyuruBaslik;
    std::string mDuyuruOid;


};






#endif // HABERDUYURUCAPS_H
