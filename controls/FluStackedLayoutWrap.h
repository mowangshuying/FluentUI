#pragma once

#include <QObject>
#include <QString>

class QWidget;
class FluStackedLayout;

/**
 * @brief Python-friendly wrapper for FluStackedLayout.
 *
 * Shiboken6 has a bug with QLayout subclasses (addLayoutOwnership not exported).
 * This wrapper holds FluStackedLayout as an instance variable (composition)
 * to avoid the QLayout inheritance issue.
 */
class FluStackedLayoutWrap : public QObject
{
    Q_OBJECT
  public:
    explicit FluStackedLayoutWrap(QWidget* parent = nullptr);
    ~FluStackedLayoutWrap() override;

    void addWidget(const QString& str, QWidget* w);
    int addWidget(QWidget* w);
    void removeWidget(const QString& str, QWidget* w);
    void setCurrentWidget(const QString& str);
    QWidget* getWidget(const QString& str);

    FluStackedLayout* layout() const;

  private:
    FluStackedLayout* m_layout;
};
