#ifndef MSP_H
#define MSP_H

#include <QString>

/*! Holding rgb values of a color
 * \brief The RgbHolder struct
 */
struct RgbHolder
{
    RgbHolder(int r, int g, int b) : red(r), green(g), blue(b) {}
    int red;
    int green;
    int blue;
};

/*! Main struct used in msp
 * \brief The MSP struct
 */
struct MSP
{
    /*! Main menus
     * \brief The Menus enum
     */
    enum Menus
    {
        MainMenu = 0,
        OptionMenu,
        MenuAmount
    };
    /*! All content pages
     * \brief The Pages enum
     */
    enum Pages
    {
        HomePage = 0,
        ToDoPage,
        HomeworkPage,
        CalendarPage,
        MoreAppsPage,
        HelpPage,
        NoPage,
        PageAmount
    };
    static const RgbHolder mainColor(){return RgbHolder(69, 137, 129);}
    static const RgbHolder sideMenuColor(){return RgbHolder(37, 70, 70);}
    static const RgbHolder sideMenuHoverColor(){return RgbHolder(50, 100, 87);}
    static const RgbHolder sideMenuPressedColor(){return RgbHolder(50, 130, 87);}
    static const RgbHolder textColor(){return RgbHolder(237, 235, 226);}
    static const RgbHolder featureColor(){return RgbHolder(154, 171, 156);}
    static const RgbHolder contrastColor(){return RgbHolder(205, 42, 49);}
};

/*! Resembling the structure of a page
 * \brief The Page struct
 */
struct Page
{
    Page(MSP::Pages p, const QString& t) : page(p), title(t) {}
    MSP::Pages page;
    QString title;
    bool operator<(const Page& other) const
    {
        bool res;
        (page < other.page) ?  res = true : res = false;
        return res;
    }
    bool operator>(const Page &other) const
    {
        bool res;
        (page > other.page) ?  res = true : res = false;
        return res;
    }
};

#endif // MSP_H
