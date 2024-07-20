#pragma once

#include <QIntValidator>

class FluIntValidator : public QIntValidator
{
  public:
    explicit FluIntValidator(QObject* parent = nullptr)
    {
    }

    FluIntValidator(int bottom, int top, QObject* parent = nullptr)
    {
    }

    QValidator::State validate(QString& input, int& pos) const override
    {
        const QValidator::State state = QIntValidator::validate(input, pos);
        if (state == QIntValidator::Acceptable || state == QIntValidator::Intermediate)
        {
            //bool isNum = true;
            //for (int i = 0; i < input.length(); i++)
            //{
            //    bool b = input.at(i) >= '0' && input.at(i) <= '9';
            //    if (!b)
            //    {
            //        isNum = false;
            //        break;
            //    }
            //}

            //if (!isNum)
            //{
            //    return QIntValidator::Invalid;
            //}

            //int nValue = input.toInt();
            //bool b = nValue >= 0 && nValue <= 255;
            //if (!b)
            //{
            //    return QIntValidator::Invalid;
            //}

            //if (input.length() > 3)
            //{
            //    return QIntValidator::Invalid;
            //}

           /// if (input.length() == 0)
           // {
           //     return QIntValidator::Invalid;
           // }
        }

        return state;
    }
};
