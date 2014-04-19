#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include "config_builder.h"

namespace Ui {
    class ConfigDialog;
}

class QTreeWidgetItem;
class CustomConfigWidgetPlugin;
class QSignalMapper;
class Plugin;
class PluginType;
class QComboBox;
class QTreeWidget;
class QListWidget;
class QTableWidget;
class ConfigMapper;

class ConfigDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit ConfigDialog(QWidget *parent = 0);
        ~ConfigDialog();

        static QString getFilterString(QWidget* widget);
        static QString getFilterString(QComboBox* widget);
        static QString getFilterString(QTreeWidget* widget);
        static QString getFilterString(QListWidget* widget);
        static QString getFilterString(QTableWidget* widget);

    private:
        void init();
        void load();
        void initPageMap();
        void initInternalCustomConfigWidgets();
        void initFormatterPlugins();
        void initPlugins();
        void initPluginsPage();
        void initPluginPage(const QString& pluginName);
        void deinitPluginPage(const QString& pluginName);
        void applyStyle(QWidget* widget, QStyle* style);
        QTreeWidgetItem* getPluginsCategoryItem() const;
        QTreeWidgetItem* getPluginsCategoryItem(PluginType* type) const;
        QTreeWidgetItem* getPluginItem(Plugin* plugin) const;
        QTreeWidgetItem* createPluginsTypeItem(const QString& widgetName, const QString& title) const;
        QTreeWidgetItem* getItemByTitle(const QString& title) const;
        void switchPageToPlugin(QTreeWidgetItem* item);
        bool isPluginCategoryItem(QTreeWidgetItem *item) const;
        void sqlFormatterAboutToUnload(Plugin* plugin);
        void sqlFormatterLoaded(Plugin* plugin);
        void updatePluginCategoriesVisibility(QTreeWidgetItem* categoryItem);
        QString collectLoadedPlugins() const;
        QHash<QWidget*,QTreeWidgetItem*> buildPageToCategoryItemMap() const;
        QList<QTreeWidgetItem*> getAllCategoryItems() const;

        Ui::ConfigDialog *ui;
        QStyle* previewStyle = nullptr;
        QHash<QString,QWidget*> nameToPage;
        QHash<QTreeWidgetItem*,QString> itemToPluginNameMap;
        QHash<PluginType*,QTreeWidgetItem*> pluginTypeToItemMap;
        QHash<Plugin*,QTreeWidgetItem*> pluginToItemMap;
        ConfigMapper* configMapper = nullptr;

    private slots:
        void switchPage(QTreeWidgetItem* item);
        void updateStylePreview();
        void apply();
        void save();
        void modified();
        void setModified(bool modified);
        void applyFilter(const QString& filter);
        void updateActiveFormatterState();
        void activeFormatterChanged(const QString& title);
        void activeFormatterConfigurePressed();
        void detailsClicked(QString pluginName);
        void loadUnloadPlugin(QTreeWidgetItem* item, int column);
        void pluginAboutToUnload(Plugin* plugin, PluginType* type);
        void pluginLoaded(Plugin* plugin, PluginType* type);
        void updatePluginCategoriesVisibility();

    public slots:
        void accept();
};

#endif // CONFIGDIALOG_H
