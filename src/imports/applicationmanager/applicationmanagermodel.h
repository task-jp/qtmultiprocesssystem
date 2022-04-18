#ifndef APPLICATIONMANAGERMODEL_H
#define APPLICATIONMANAGERMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtQml/qqml.h>
#include <QtMultiProcessSystem/QMpsApplicationManager>

class ApplicationManagerModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QMpsApplicationManager *manager MEMBER applicationManager NOTIFY applicationManagerChanged)
public:
    explicit ApplicationManagerModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void applicationManagerChanged(QMpsApplicationManager* applicationManager);

private:
    QMpsApplicationManager *applicationManager = nullptr;
    QList<QMpsApplication> appsForMenu;
};

#endif // APPLICATIONMANAGERMODEL_H
