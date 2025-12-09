#ifndef APPLICATIONMANAGERMODEL_H
#define APPLICATIONMANAGERMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtQml/qqml.h>
#include <QtMultiProcessSystem/QMpsApplicationManager>

class ApplicationManagerModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QML_ADDED_IN_VERSION(1, 0)
#endif
    Q_PROPERTY(QMpsApplicationManager *manager MEMBER applicationManager NOTIFY applicationManagerChanged)
    Q_PROPERTY(QMpsApplication::Attributes excludeAttributes MEMBER excludeAttributes NOTIFY excludeAttributesChanged)
    Q_PROPERTY(QMpsApplication::Attributes includeAttributes MEMBER includeAttributes NOTIFY includeAttributesChanged)
    Q_PROPERTY(QStringList filters MEMBER filters NOTIFY filtersChanged)
public:
    explicit ApplicationManagerModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void applicationManagerChanged(QMpsApplicationManager* applicationManager);
    void excludeAttributesChanged(QMpsApplication::Attributes excludeAttributes);
    void includeAttributesChanged(QMpsApplication::Attributes includeAttributes);
    void filtersChanged(const QStringList &filters);

private:
    QMpsApplicationManager *applicationManager = nullptr;
    QMpsApplication::Attributes excludeAttributes = QMpsApplication::SystemUI| QMpsApplication::Daemon;
    QMpsApplication::Attributes includeAttributes = QMpsApplication::None;
    QStringList filters;
    QList<QMpsApplication> appsForMenu;
};

#endif // APPLICATIONMANAGERMODEL_H
