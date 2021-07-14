// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef GMAILSERVICEROOT_H
#define GMAILSERVICEROOT_H

#include "services/abstract/cacheforserviceroot.h"
#include "services/abstract/serviceroot.h"

class GmailNetworkFactory;

class GmailServiceRoot : public ServiceRoot, public CacheForServiceRoot {
  Q_OBJECT

  public:
    explicit GmailServiceRoot(RootItem* parent = nullptr);

    void setNetwork(GmailNetworkFactory* network);
    GmailNetworkFactory* network() const;

    virtual bool downloadAttachmentOnMyOwn(const QUrl& url) const;
    virtual QList<QAction*> contextMenuMessagesList(const QList<Message>& messages);
    virtual QList<QAction*> serviceMenu();
    virtual bool isSyncable() const;
    virtual bool canBeEdited() const;
    virtual bool editViaGui();
    virtual bool supportsFeedAdding() const;
    virtual bool supportsCategoryAdding() const;
    virtual void start(bool freshly_activated);
    virtual QString code() const;
    virtual QString additionalTooltip() const;
    virtual void saveAllCachedData(bool ignore_errors);
    virtual QVariantHash customDatabaseData() const;
    virtual void setCustomDatabaseData(const QVariantHash& data);
    virtual QList<Message> obtainNewMessages(const QList<Feed*>& feeds,
                                             const QHash<ServiceRoot::BagOfMessages, QStringList>& stated_messages,
                                             const QHash<QString, QStringList>& tagged_messages);

  protected:
    virtual RootItem* obtainNewTreeForSyncIn() const;

  private slots:
    void replyToEmail();
    void writeNewEmail();

  private:
    void updateTitle();

  private:
    GmailNetworkFactory* m_network;
    QAction* m_actionReply;
    Message m_replyToMessage;
};

inline void GmailServiceRoot::setNetwork(GmailNetworkFactory* network) {
  m_network = network;
}

inline GmailNetworkFactory* GmailServiceRoot::network() const {
  return m_network;
}

#endif // GMAILSERVICEROOT_H
