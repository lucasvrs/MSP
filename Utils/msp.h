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
    static const RgbHolder mainColor(){return RgbHolder(48, 230, 88);}
    static const RgbHolder sideMenuColor(){return RgbHolder(26, 148, 55);}
    static const RgbHolder sideMenuHoverColor(){return RgbHolder(66, 184, 92);}
    static const RgbHolder sideMenuPressedColor(){return RgbHolder(1, 110, 25);}
    static const RgbHolder textColor(){return RgbHolder(255, 255, 255);}
    static const RgbHolder darkLightTextColor(){return RgbHolder(200, 200, 200);};
    static const RgbHolder darkTextColor(){return RgbHolder(0, 0, 0);}
    static const RgbHolder highlightColor(){return RgbHolder(144, 205, 45);}
    static const RgbHolder lightHighlightColor(){return RgbHolder(196, 240, 125);}
    static const RgbHolder darkHighlightColor(){return RgbHolder(112, 170, 19);}
    static const RgbHolder warmContrastColor(){return RgbHolder(222, 133, 49);}
    static const RgbHolder warmDarkContrastColor(){return RgbHolder(185, 101, 21);}
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
