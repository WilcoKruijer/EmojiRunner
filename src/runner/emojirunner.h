#ifndef EMOJIRUNNER_H
#define EMOJIRUNNER_H

#include <KRunner/AbstractRunner>
#include "core/EmojiCategory.h"
#include <QtCore>

#ifdef XDO_LIB
// For autotyping
extern "C" {
#include <xdo.h>
}
#endif


class EmojiRunner : public Plasma::AbstractRunner {
Q_OBJECT
public:
    ~EmojiRunner() override;

public:
    EmojiRunner(QObject *parent, const QVariantList &args);

    const QRegularExpression prefixRegex = QRegularExpression(R"(emoji(?: +(.*))?)");
    QList<EmojiCategory> emojiCategories;
    EmojiCategory favouriteCategory;
    QFileSystemWatcher watcher;
    int pasteTimeout;
    bool tagSearchEnabled, descriptionSearchEnabled, globalSearchEnabled, singleRunnerModePaste;
    const QLatin1String queryPrefix = QLatin1String("emoji");
    QList<QAction *> matchActionList;

    Plasma::QueryMatch createQueryMatch(const Emoji *emoji, qreal relevance);

#ifdef XDO_LIB
    xdo_t *xdo = xdo_new(nullptr);

#endif

    /**
     * Emits the Ctrl+V key combination. If the xdo.h file was available at compile time it uses the api,
     * otherwise it starts a new xdotool process
     */
    void emitCTRLV();

    /**
     * Deletes the emojis
     */
    void deleteEmojiPointers();

public: // Plasma::AbstractRunner API
    void match(Plasma::RunnerContext &context) override;
    QList<QAction*> actionsForMatch(const Plasma::QueryMatch &match) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;

public Q_SLOTS:
    void reloadPluginConfiguration(const QString &configFile = "");
};

#endif
