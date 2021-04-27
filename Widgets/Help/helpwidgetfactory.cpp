#include "helpwidgetfactory.h"
#include <QDomDocument>
#include <QDebug>
/*!
 * \brief Constructor
 */
HelpWidgetFactory::HelpWidgetFactory() :
    m_reader("./../FinalMsp/Widgets/Help/Help.xml")
{

}
/*!
 * \brief create widgets from XML-file
 * \return list of widgetItems
 */
QList<WidgetItem*> HelpWidgetFactory::widgets()
{
  QList<WidgetItem*> widgets;
  for(QDomElement e : *m_reader.allElemsUnderRoot()){
      if(e.nodeName() == "data")
      {

          for(const QDomElement &cE : *m_reader.allElemsUnderElem(e))
          {
               WidgetItem *item = new WidgetItem();
            item->setName(cE.attribute("name"));
            for(const QDomElement &fE : *m_reader.allElemsUnderElem(cE))
            {
                if(fE.tagName() == "picture")
                {
                    item->setPicLink(fE.text());
                }
                if(fE.tagName() == "description")
                {
                    item->setDescription(fE.text());
                }
                if(fE.tagName() == "functionality")
                {
                    item->setFunc(fE.text());
                }
                if(fE.tagName() == "shortcuts")
                {
                    for(const QDomElement &sE : *m_reader.allElemsUnderElem(fE))
                    {
                        for(const QDomElement &seE : *m_reader.allElemsUnderElem(sE))
                        {

                        QList<Shortcut> hlp_list = item->shortList();
                        Shortcut shorty;

                        if(seE.tagName() == "primary")
                        {
                            shorty.shorty = seE.text();

                        }
                        if(seE.tagName() == "function")
                        {
                            shorty.shortyFunc = seE.text();

                        }
                        hlp_list.append(shorty);
                        item->setShortList(hlp_list);


                    }
                    }
                }

            }
             widgets.append(item);
          }

      }
  }
return widgets;
}
