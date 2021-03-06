#include "sqlitevacuum.h"
#include "sqlitequerytype.h"

#include <parser/statementtokenbuilder.h>

SqliteVacuum::SqliteVacuum()
{
    queryType = SqliteQueryType::Vacuum;
}

SqliteVacuum::SqliteVacuum(const SqliteVacuum& other) :
    SqliteQuery(other), database(other.database)
{
}

SqliteVacuum::SqliteVacuum(const QString& name)
    : SqliteVacuum()
{
    if (!name.isNull())
        database = name;
}

SqliteStatement*SqliteVacuum::clone()
{
    return new SqliteVacuum(*this);
}

QStringList SqliteVacuum::getDatabasesInStatement()
{
    return getStrListFromValue(database);
}

TokenList SqliteVacuum::getDatabaseTokensInStatement()
{
    if (!tokensMap.contains("nm"))
        return TokenList();

    return getTokenListFromNamedKey("nm");
}

QList<SqliteStatement::FullObject> SqliteVacuum::getFullObjectsInStatement()
{
    QList<FullObject> result;

    // Db object
    FullObject fullObj = getFirstDbFullObject();
    if (fullObj.isValid())
        result << fullObj;

    return result;
}


TokenList SqliteVacuum::rebuildTokensFromContents()
{
    StatementTokenBuilder builder;
    builder.withTokens(SqliteQuery::rebuildTokensFromContents());
    builder.withKeyword("VACUUM").withOperator(";");
    return builder.build();
}
