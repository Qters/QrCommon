#ifndef ITRANSLATOR_H
#define ITRANSLATOR_H

#include <qevent.h>
#include <qwidget.h>

/*!
 * \brief tranlate interface
 */
class QrTranslator
{
public:
    virtual void retranslate() = 0;
};

/*!
  DEMO:

    class SomeWidget : public QWidget, QrTranslator {
        LANGUAGE_CHANGE_FUNC

    public:
        //  translate this widget's language
        virtual void retranslate() {
            label.setText(tr(""));
        }

    }
  */

#define LANGUAGE_CHANGE_EVENT \
protected: \
virtual void changeEvent(QEvent *event) override { \
    if (event->type() == QEvent::LanguageChange) \
    { \
        retranslate(); \
    } \
 \
    QWidget::changeEvent(event); \
} \
public: \
    virtual void retranslate() override;

#endif // ITRANSLATOR_H
