/**************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
**************************************************************************/

#ifndef QINSTALLER_REPOSITORYGEN_H
#define QINSTALLER_REPOSITORYGEN_H

#include <QHash>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QDomDocument>

namespace QInstallerTools {


struct PackageInfo
{
    QString name;
    QString version;
    QString directory;
    QStringList dependencies;
    QStringList copiedFiles;
    QString metaFile;
    QString metaNode;
};
typedef QVector<PackageInfo> PackageInfoVector;

enum FilterType {
    Include,
    Exclude
};

void printRepositoryGenOptions();
QString makePathAbsolute(const QString &path);
void copyWithException(const QString &source, const QString &target, const QString &kind = QString());

PackageInfoVector createListOfPackages(const QStringList &packagesDirectories, QStringList *packagesToFilter,
    FilterType ftype);

PackageInfoVector createListOfRepositoryPackages(const QStringList &repositoryDirectories, QStringList *packagesToFilter,
    FilterType filterType);

QHash<QString, QString> buildPathToVersionMapping(const PackageInfoVector &info);

void compressMetaDirectories(const QString &repoDir, const QString &existingUnite7zUrl,
    const QHash<QString, QString> &versionMapping, bool createSplitMetadata, bool createUnifiedMetadata);

QStringList unifyMetadata(const QString &repoDir, const QString &existingRepoDir, QDomDocument doc);
void splitMetadata(const QStringList &entryList, const QString &repoDir, QDomDocument doc,
                   const QHash<QString, QString> &versionMapping);

void copyMetaData(const QString &outDir, const QString &dataDir, const PackageInfoVector &packages,
    const QString &appName, const QString& appVersion, const QStringList &uniteMetadatas);
void copyComponentData(const QStringList &packageDir, const QString &repoDir, PackageInfoVector *const infos);

void filterNewComponents(const QString &repositoryDir, QInstallerTools::PackageInfoVector &packages);

QString existingUniteMeta7z(const QString &repositoryDir);

} // namespace QInstallerTools

#endif // QINSTALLER_REPOSITORYGEN_H
