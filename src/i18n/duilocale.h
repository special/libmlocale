/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of libdui.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef DUILOCALE_H
#define DUILOCALE_H

#include "duiexport.h"

#include <QtGlobal>
#include <QObject>

class QString;
class QStringList;
class QDateTime;

class DuiCollator;
class DuiAbstractName;
class DuiCalendar;
class DuiBreakIteratorPrivate;

class DuiLocalePrivate;

/*!
 * \class DuiLocale
 *
 * \brief DuiLocale is a class that implements locale dependent data formatting as well as translation, collation and calendar systems.
 *
 * For more general information about Internationalization in libdui
 * see also the <a href="i18n.html">Internationalization Guidelines</a>
 *
 * The locale system in Direct UI is separated into different
 * categories. These correspond roughly with the LC_* environment
 * variables of POSIX. DuiLocale is created with one main
 * language/country information for it, but can be overridden with
 * category specific settings. E.g.  having messages in
 * english/u.s. but using finnish collation (DuiLcCollation category)
 * and number formatting (DuiLcNumeric).
 *
 * The calendar system in Direct UI supports a number of non-Gregorian
 * calendar systems. The calendar is used to create presentations of
 * date and time.
 *
 * The collation system in Direct UI supports a number of collation
 * systems. The actual collation is done with the DuiCollator class.
 *
 * The translation system in Direct UI differs a bit from the usual
 * practice used in any other translation system (e.g, Qt's tr() or
 * GNU's gettext). In Direct UI, a developer uses both logical names
 * and Engineering English to translate a string. The logical names are
 * useful when you have to maintain tens of thousands strings in your
 * translation file sets. Whenever no translation is available, the
 * Engineering English version, which is auto-generated from the source code,
 * is displayed instead of the logical names to make testing easier.
 * The displayed Engineering English is prefixed with "!! " to make it
 * obvious that no translation was found and a proper translation still
 * needs to be added.  Internally, the Direct UI translation system
 * uses the Qt translation system (using the QTranslator class). The
 * translation source file is in .ts format version 3.0. Usually the
 * translation source file is not generated from code, but rather
 * generated by some other means (e.g from the UI specification).
 *
 * If DuiLocale is instantiated without any parameters, it will create
 * the locale based on the settings in the global settings. If the
 * settings are not available it creates the locale based on the LANG
 * environment variable. If one wants to react when the settings are
 * changed, one can connect to the settingsChanged() signal and call
 * the connectSettings() method.
 *
 * \note The methods are not thread-safe. For number/string formatting etc. the class is re-entrant. If one needs to have formatting in multiple threads it is suggested to create separate locales.
 *
 * Examples:
 *
 * \verbatim
 * DuiLocale locale("en_US");
 * // format a number to a string using US English conventions:
 * QString numberString = locale.formatNumber(123456789);
 * \endverbatim
 *
 * Install a translation catalog for Finnish, make Finnish the defautl
 * and translate a message to Finnish:
 *
 * \verbatim
 * DuiLocale locale("fi");
 * // install a translation catalog:
 * locale.installTrCatalog("catalogname");
 * // make the locale with this translation catalog the default:
 * DuiLocale::setDefault(locale);
 *
 * //% "Hello"
 * QString translatedString = qtTrId("hello_msg");
 * DuiLocale defaultLocale; // English settings are copied
 * \endverbatim
 */


class DUI_EXPORT DuiLocale : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief enum for Date formatting.
     *
     * This correlates closely with the <a
     * href="http://userguide.icu-project.org/formatparse/datetime#TOC-Producing-Normal-Date-Formats-for-a">
     * date type in ICU</a> and Unicode CLDR
     */
    enum DateType {
        DateNone,
        DateShort,
        DateMedium,
        DateLong,
        DateFull
    };

    /*!
     * \brief enum for Time formatting.
     *
     * This correlates closely with the <a
     * href="http://userguide.icu-project.org/formatparse/datetime#TOC-Producing-Normal-Date-Formats-for-a">
     * time type in ICU</a> and Unicode CLDR
     */
    enum TimeType {
        TimeNone,
        TimeShort,
        TimeMedium,
        TimeLong,
        TimeFull
    };

    // NOTE: could add LC_CTYPE, LC_PAPER, LC_ADDRESS, LC_TELEPHONE,
    // LC_MEASUREMENT, LC_IDENTIFICATION?

    //! Category type for the locale
    enum Category {DuiLcMessages, DuiLcTime, DuiLcCollate,
                   DuiLcNumeric, DuiLcMonetary, DuiLcName
                  };

    //! Set of possible collations
    enum Collation {DefaultCollation, PhonebookCollation, PinyinCollation,
                    TraditionalCollation, StrokeCollation, DirectCollation,
                    PosixCollation, Big5hanCollation, Gb2312hanCollation
                   };

    //! Calendar type.
    enum CalendarType {DefaultCalendar, GregorianCalendar, IslamicCalendar,
                       ChineseCalendar, IslamicCivilCalendar, HebrewCalendar,
                       JapaneseCalendar, BuddhistCalendar, PersianCalendar,
                       CopticCalendar, EthiopicCalendar
                      };

    enum Weekday {Monday = 1, Tuesday, Wednesday, Thursday, Friday,
                  Saturday, Sunday
                 };


    //! Return type for DuiCollator::compare(). Denotes the order of two strings.
    enum Comparison {LessThan = -1, Equal = 0, GreaterThan = 1};


    //! Type for locale dependant date symbol presentation
    enum DateSymbolContext {DateSymbolFormat, DateSymbolStandalone};

    //! Length type for date symbol presentation
    enum DateSymbolLength {DateSymbolAbbreviated, DateSymbolWide, DateSymbolNarrow};



    static DuiLocale *createSystemDuiLocale();
    static DuiLocale createCLocale();

    explicit DuiLocale(QObject *parent = 0);

    /*!
     * Constructs a DuiLocale from a ICU format locale ID string
     * \param localeName ICU format locale ID string.
     * \param parent the Object’s parent
     *
     * For details about ICU format locale ID strings
     * see http://userguide.icu-project.org/locale .
     *
     * <table border="1">
     * <caption>
     *   <big><b>
     *     Examples for ICU format locale ID strings
     *   </b></big>
     * </caption>
     * <tr>
     *   <th>Locale ID</th>
     *   <th>Language</th>
     *   <th>Script</th>
     *   <th>Country</th>
     *   <th>Variant</th>
     *   <th>Keywords</th>
     *   <th>Comment</th>
     * </tr>
     * <tr>
     *   <td>fi_FI</td>
     *   <td>fi</td>
     *   <td></td>
     *   <td>FI</td>
     *   <td></td>
     *   <td></td>
     *   <td>Finnish language in Finland, default sorting order</td>
     * <tr>
     *   <td>fi_FI@collation=phonebook</td>
     *   <td>fi</td>
     *   <td></td>
     *   <td>FI</td>
     *   <td></td>
     *   <td>collation=phonebook</td>
     *   <td>Finnish language in Finland, phonebook sorting order</td>
     * </tr>
     * <tr>
     *   <td>zh_CN@collation=stroke;calendar=chinese</td>
     *   <td>zh</td>
     *   <td></td>
     *   <td>CN</td>
     *   <td></td>
     *   <td>collation=stroke;calendar=chinese</td>
     *   <td>Simplified Chinese with sorting via stroke-count and Chinese calendar</td>
     * </tr>
     * </tr>
     */
    explicit DuiLocale(const QString &localeName, QObject *parent = 0);
    DuiLocale(const DuiLocale &other, QObject *parent = 0);

    virtual ~DuiLocale();

    DuiLocale &operator=(const DuiLocale &other);


    /*!
     * \brief Sets the default locale.
     */
    static void setDefault(const DuiLocale &locale);

    /*!
     * \brief Returns true if DuiLocale is valid and can be used
     */
    bool isValid() const;

    /*!
     * \brief Sets category with specified locale string
     * \param localeName ICU format locale ID string.
     */
    void setCategoryLocale(Category category, const QString &localeName);

    /*!
     * \brief Sets the collation mode
     */
    void setCollation(Collation collation);

    /*!
     * \brief Returns the collation mode
     */
    Collation collation() const;

    /*!
     * \brief Sets calendar type
     */
    void setCalendarType(CalendarType calendar);

    /*!
     * \brief Returns calendar type
     */
    CalendarType calendarType() const;

    /*!
     * \brief Returns a DuiCollator which compares QStrings based on language/country/collation rules
     */
    DuiCollator collator() const;

    /*!
     * \brief Returns the endonym of the language of the locale
     *
     * The language <a href="http://en.wikipedia.org/wiki/Endonym">endonym</a> is the
     * name of the language which is used by the native speakers of
     * this language.
     *
     * <table border="1">
     * <caption>
     *  <big><b>Examples for language endonyms</b></big>
     * </caption>
     * <tr>
     *    <th>English exonym</th><th>Language endonym</th>
     * </tr>
     * <tr>
     *    <td>German</td><td>Deutsch</td>
     * </tr>
     * <tr>
     *    <td>Russian</td><td>русский язык</td>
     * </tr>
     * <tr>
     *    <td>Japanese</td><td>日本語</td>
     * </tr>
     * </table>
     *
     */
    QString languageEndonym() const;

    /*!
     * \brief Returns the endonym of the country of the locale
     *
     * The country <a href="http://en.wikipedia.org/wiki/Endonym">endonym</a>
     * is the name of the country which is used by the inhabitants of that country.
     *
     * <table border="1">
     * <caption>
     *  <big><b>Examples for country endonyms</b></big>
     * </caption>
     * <tr>
     *    <th>English exonym</th><th>Language endonym</th>
     * </tr>
     * <tr>
     *    <td>Germany</td><td>Deutschland</td>
     * </tr>
     * <tr>
     *    <td>Russia</td><td>Россия</td>
     * </tr>
     * <tr>
     *    <td>Japan</td><td>日本</td>
     * </tr>
     * </table>
     *
     */
    QString countryEndonym() const;

    /*!
     * \brief Returns the language code of the locale in ISO-639 format
     */
    QString language() const;

    /*!
     * \brief Returns the country code of the locale in ISO-3166 format
     */
    QString country() const;

    /*!
     * \brief Returns the script code of the locale in ISO-15924 format
     */
    QString script() const;

    /*!
     * \brief Returns the variant appended to the locale
     */
    QString variant() const;

    /*!
     * \brief Returns the string representation of the locale
     */
    QString name() const;

    /*!
     * \brief Returns the text direction of the locale
     */
    Qt::LayoutDirection textDirection() const;

    /*!
     * \brief Returns the language code of the category in ISO-639 format
     */
    QString categoryLanguage(Category category) const;

    /*!
     * \brief Returns the country code of the category in ISO-3166 format
     */
    QString categoryCountry(Category category) const;

    /*!
     * \brief Returns the variant code appended to the category
     */
    QString categoryVariant(Category category) const;

    /*!
     * \brief Returns the string representation of the category
     */
    QString categoryName(Category category) const;

    ////////////////////////////////////////
    /////   number formatting methods: /////

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     */
    QString formatNumber(qlonglong i) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     */
    QString formatNumber(short i) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     */
    QString formatNumber(int i) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     * \param precision number of fractional digits
     */
    QString formatNumber(double i, int precision = -1) const;

    /*!
     * \brief Returns the string representation of a number
     * \param i number to format
     */
    QString formatNumber(float i) const;

    /*!
     * \brief Returns the string representation of a number as percentage
     * \param i number to format
     * \param decimals number of digits shown after decimal separator
     */
    QString formatPercent(double i, int decimals = 0) const;

    /*!
     * \brief Formats an amount of currency
     * \param amount amount to format
     * \param currency three letter currency code in ISO-4217 format, e.g. EUR or USD
     */
    QString formatCurrency(double amount, const QString &currency) const;

    /*!
     * \brief Creates a string presentation for a date time with explicit format lengths
     * \param dateTime time object to create representation from
     * \param dateType style of date formatting
     * \param timeType style of time formatting
     * \param calendarType calendar type to use for formatting
     *
     * If dateType is DuiLocale::DateNone <b>and</b> timeType is DuiLocale::TimeNone,
     * an empty string is returned.
     */
    QString formatDateTime(const QDateTime &dateTime, DateType dateType = DateLong,
                           TimeType timeType = TimeLong,
                           CalendarType calendarType = DefaultCalendar) const;

    /*!
     * \brief String presentation with explicit calendar type
     * \param dateTime time to format
     * \param calendarType calendar to use
     */
    QString formatDateTime(const QDateTime &dateTime, CalendarType calendarType) const;

    /*!
     * \brief Formats DuiCalendar using its native calendar system
     * \param duiCalendar Calendar holding the datetime to format
     * \param datetype format for date
     * \param timetype format for time
     *
     * If dateType is DuiLocale::DateNone <b>and</b> timeType is DuiLocale::TimeNone,
     * an empty string is returned.
     */
    QString formatDateTime(const DuiCalendar &duiCalendar, DateType datetype = DateLong,
                           TimeType timetype = TimeLong) const;

    QString formatDateTimeICU(const QDateTime &dateTime,
                              const QString &formatString) const;
    QString formatDateTimeICU(const DuiCalendar &duiCalendar,
                              const QString &formatString) const;
    /*!
     * \brief creates a string presentation for a QDateTime with specific format string
     * \param dateTime QDateTime to format
     * \param formatString in ISO-14652 date time format
     *
     * \sa formatDateTime(const DuiCalendar &duiCalendar, const QString &formatString) const
     */
    QString formatDateTime(const QDateTime &dateTime,
                           const QString &formatString) const;
    // divergence: not implemented modified field descriptors (%Ec, %EC, %EY etc)

    /**
    \brief Formats a date string based on ISO-14652 (draft) pattern

    \sa formatDateTime(const QDateTime &dateTime, const QString &formatString) const;

    For more information about the format characters used here see
    <a href="http://www.open-std.org/jtc1/SC22/WG20/docs/n972-14652ft.pdf">
    ISO-14652 (draft)
    </a>
    or
    <a href="http://linux.die.net/man/1/date">
    the man page of <verbatim>date<verbatim>
    </a>
    or
    <a href="http://www.gnu.org/s/libc/manual/html_node/Formatting-Calendar-Time.html">
    the documentation of the glibc function <verbatim>strftime</verbatim>
    </a>.

    The pattern may contain the following symbols to be replaced with
    the corresponding information:
     - \%a FDCC-set's abbreviated weekday name.
     - \%A FDCC-set's full weekday name.
     - \%b FDCC-set's abbreviated month name.
     - \%B FDCC-set's full month name.
     - \%c FDCC-set's appropriate date and time representation.
     - \%C Century (a year divided by 100 and truncated to integer) as decimal number (00-99).
     - \%d Day of the month as a decimal number (01-31).
     - \%D Date in the format mm/dd/yy.
     - \%e Day of the month as a decimal number (1-31 in at two-digit field with leading &lt;space&gt; fill).
     - \%F The date in the format YYYY-MM-DD (An ISO 8601 format).
     - \%g Week-based year within century, as a decimal number (00-99).
     - \%G Week-based year with century, as a decimal number (for example 1997).
     - \%h A synonym for %b.
     - \%H Hour (24-hour clock), as a decimal number (00-23).
     - \%I Hour (12-hour clock), as a decimal number (01-12).
     - \%j Day of the year, as a decimal number (001-366).
     - \%m Month, as a decimal number (01-13).
     - \%M Minute, as a decimal number (00-59).
     - \%n A &lt;newline&gt; character.
     - \%p FDCC-set's equivalent of either AM or PM.
     - \%r 12-hour clock time (01-12), using the AM/PM notation.
     - \%R 24-hour clock time, in the format "%H:%M".
     - \%S Seconds, as a decimal number (00-61).
     - \%t A &lt;tab&gt; character.
     - \%T 24-hour clock time, in the format HH:MM:SS.
     - \%u Weekday, as a decimal number (1(Monday)-7).
     - \%U Week number of the year (Sunday as the first day of the week) as a
       decimal number (00-53). All days in a new year preceding the first
       Sunday are considered to be in week 0.
     - \%v Week number of the year, as a decimal number with two digits including
       a possible leading zero, according to "week" keyword.
     - \%V Week of the year (Monday as the first day of the week), as a decimal
       number (01-53). The method for determining the week number is as
       specified by ISO 8601.
     - \%w Weekday, as a decimal number (0(Sunday)-6).
     - \%W Week number of the year (Monday as the first day of the week), as a
       decimal number (00-53). All days in a new year preceding the first
       Monday are considered to be in week 0.
     - \%x FDCC-set's appropriate date representation.
     - \%X FDCC-set's appropriate time representation.
     - \%y Year within century (00-99).
     - \%Y Year with century, as a decimal number.
     - \%z The offset from UTC in the ISO 8601 format "-0430" (meaning 4 hours
       30 minutes behind UTC, west of Greenwich), or by no characters if no
       time zone is determinable.
     - \%Z Time-zone name, or no characters if no time zone is determinable.
     - \%% A &lt;percent-sign&gt; character.
    */
    QString formatDateTime(const DuiCalendar &duiCalendar,
                           const QString &formatString) const;

    /*!
     * \brief Creates a datetime object from a string with explicit format lengths.
     * \param dateTime string to parse
     * \param dateType style of date formatting
     * \param timeType style of time formatting
     * \param calendarType calendar to use for formatting
     *
     * If dateType is DuiLocale::DateNone <b>and</b> timeType is DuiLocale::TimeNone,
     * an invalid QDateTime is returned.
     */
    QDateTime parseDateTime(const QString &dateTime, DateType dateType = DateLong,
                            TimeType timeType = TimeLong,
                            CalendarType calendarType = DefaultCalendar) const;

    /*!
     * \brief Creates a datetime object from a string with explicit calendar type.
     * \param dateTime string to parse
     * \param calendarType calendar to use
     */
    QDateTime parseDateTime(const QString &dateTime, CalendarType calendarType) const;

    /*!
     * \brief Returns the locale dependant name for a month number
     */
    QString monthName(const DuiCalendar &duiCalendar, int monthNumber) const;

    /*!
     * \brief Returns the locale dependant name for a month using context information
     */
    QString monthName(const DuiCalendar &duiCalendar, int monthNumber,
                      DateSymbolContext context, DateSymbolLength symbolLength) const;

    /*!
     * \brief Returns locale dependant weekday name
     */
    QString weekdayName(const DuiCalendar &duiCalendar, int weekday) const;


    /*!
     * \brief Returns locale dependant weekday name using context information
     */
    QString weekdayName(const DuiCalendar &duiCalendar, int weekday,
                        DateSymbolContext context, DateSymbolLength symbolLength) const;

    // TODO: add versions for QDate and QTime?

    ////////////////////////////////
    //// ID translation scheme /////

    /*!
     * \brief Copies translations from another DuiLocale
     * the catalogs are reloaded based on the locale settings
     */
    void copyCatalogsFrom(const DuiLocale &other);

    /*!
     * \brief installs a translation catalog
     *
     * Adds this translation catalog to the list of translation catalogs
     * used by this DuiLocale.
     *
     * The list of catalogs used by the default locale is the list of
     * catalogs which will be used when translating strings with qtTrId() or tr().
     *
     * \sa setDefault(const DuiLocale &locale)
     */
    void installTrCatalog(const QString &name);

    /*!
     * \brief removes a translation catalog
     *
     * Removes the catalog from the list of translation catalogs used by this
     * DuiLocale.
     */
    void removeTrCatalog(const QString &name);

    /*!
     * \brief tr() compatibility translation method.
     * \param context context of the translation
     * \param sourceText text to translate
     * \param comment about the translation. may be helpful when creating translation files
     * \param n plurality
     */
    QString translate(const char *context, const char *sourceText,
                      const char *comment = 0, int n = -1);

    /*!
     * \brief Sets the DataPaths for locale system to given paths.
     * This should be called at most once before creating any DuiLocale instances
     * Data itself should be in the ICU specific subdirectory at the given paths, e.g.
     * somePath/icudt42l/
     */
    static void setDataPaths(const QStringList &dataPaths);

    /*!
     * \brief Sets the DatPaths to given path
     */
    static void setDataPath(const QString &dataPath);

    /*!
     * \brief Sets the paths that are used as base directories for using translations
     * The translation path modification methods are not thread-safe.
     */
    static void setTranslationPaths(const QStringList &paths);

    /*!
     * \brief Append a path to the translation file lookup directories.
     */
    static void addTranslationPath(const QString &path);

    /*!
     * \brief Removes a path
     */
    static void removeTranslationPath(const QString &path);

    /*!
     * \brief Returns the list of current translation file base paths
     */
    static QStringList translationPaths();

    /*!
     * \brief Monitors all changes in the locale related gconf keys
     *
     * After calling this method, all changes in the locale related
     * gconf keys will change this locale according to the changes in the
     * gconf keys, set this locale as the new system default locale
     * and emit the settingsChanged() signal.
     */
    void connectSettings();

    /*!
     * \brief Disconnects from change monitoring in settings
     * After calling this method, all changes in the settings
     * will no longer emit settingsChanged() signal
     */
    void disconnectSettings();

Q_SIGNALS:
    void settingsChanged();
    /*!
     * \brief Signal emitted when the default system locale changes.
     */
    void localeSettingsChanged();

protected:

    /*!
     * \brief Returns the default locale object.
     */
    static DuiLocale &getDefault();

private:
    // not implemented now
    bool operator==(const DuiLocale &other) const;
    bool operator!=(const DuiLocale &other) const;

    // global default locale
    static DuiLocale *s_systemDefault;

    // private info is kept away from the public header
    DuiLocalePrivate *const d_ptr;
    Q_DECLARE_PRIVATE(DuiLocale)

    friend class DuiCalendar;
    friend class DuiCollator;
    friend class DuiIcuBreakIteratorPrivate;

private Q_SLOTS:
    void refreshSettings();
};

#endif
