#ifndef UILANGUAGE_H
#define UILANGUAGE_H

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QComboBox>
#include <QGroupBox>
#include <QHash>
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QSettings>
#include <QTableWidget>
#include <QVariant>
#include <QWidget>

#include <functional>

namespace UiLanguage
{
inline bool isArabic()
{
    return qApp &&
           qApp->property("atharLanguage").toString() == "ar";
}

inline const QHash<QString, QString> &dictionary()
{
    static const QHash<QString, QString> values = {
        {"Dashboard", QString::fromUtf8(u8"لوحة التحكم")},
        {"Simulation", QString::fromUtf8(u8"المحاكاة")},
        {"Services", QString::fromUtf8(u8"الخدمات")},
        {"Fault Injection", QString::fromUtf8(u8"حقن الأعطال")},
        {"Network View", QString::fromUtf8(u8"عرض الشبكة")},
        {"History", QString::fromUtf8(u8"السجل")},
        {"Reports", QString::fromUtf8(u8"التقارير")},
        {"Theme", QString::fromUtf8(u8"المظهر")},
        {"Dark", QString::fromUtf8(u8"داكن")},
        {"Light", QString::fromUtf8(u8"فاتح")},
        {"Language", QString::fromUtf8(u8"اللغة")},
        {"ATHAR", QString::fromUtf8(u8"أثر")},
        {"FAULT LAB 2", QString::fromUtf8(u8"مختبر الأعطال 2")},
        {"Simulation Dashboard", QString::fromUtf8(u8"لوحة المحاكاة")},
        {"Real-time workload metrics, runtime failures, latency and infrastructure health.", QString::fromUtf8(u8"مؤشرات حمل العمل الفعلية، وإخفاقات التشغيل، وزمن الاستجابة، وحالة البنية التحتية في الوقت الحقيقي.")},
        {"SYSTEM READY", QString::fromUtf8(u8"النظام جاهز")},
        {"SIMULATION RUNNING", QString::fromUtf8(u8"المحاكاة قيد التشغيل")},
        {"SIMULATION STOPPED", QString::fromUtf8(u8"تم إيقاف المحاكاة")},
        {"SIMULATION FINISHED", QString::fromUtf8(u8"اكتملت المحاكاة")},
        {"PROCESSED REQUESTS", QString::fromUtf8(u8"الطلبات المعالجة")},
        {"SUCCESS RATE", QString::fromUtf8(u8"نسبة النجاح")},
        {"FAILED REQUESTS", QString::fromUtf8(u8"الطلبات الفاشلة")},
        {"AVG. LATENCY", QString::fromUtf8(u8"متوسط زمن الاستجابة")},
        {"Requests processed during the current run", QString::fromUtf8(u8"الطلبات التي تمت معالجتها أثناء التشغيل الحالي")},
        {"Runtime success rate across processed requests", QString::fromUtf8(u8"نسبة النجاح الفعلية بين الطلبات المعالجة")},
        {"Observed runtime failures, including overload", QString::fromUtf8(u8"إخفاقات التشغيل الفعلية بما فيها الحمل الزائد")},
        {"Average latency of successful requests", QString::fromUtf8(u8"متوسط زمن استجابة الطلبات الناجحة")},
        {"Runtime Failure Rate is calculated from actual failed requests. It is separate from a service's configured fault probability.", QString::fromUtf8(u8"يتم حساب معدل فشل التشغيل من الطلبات التي فشلت فعليا، وهو منفصل عن احتمال الفشل المضبوط للخدمة.")},
        {"Infrastructure Health", QString::fromUtf8(u8"حالة البنية التحتية")},
        {"Configured service state and active injected faults.", QString::fromUtf8(u8"حالة الخدمات المضبوطة والأعطال النشطة المحقونة.")},
        {"Simulation engine unavailable.", QString::fromUtf8(u8"محرك المحاكاة غير متاح.")},
        {"Simulation Control Center", QString::fromUtf8(u8"مركز التحكم بالمحاكاة")},
        {"Configure workload parameters and run the simulation engine.", QString::fromUtf8(u8"اضبط معلمات حمل العمل وشغل محرك المحاكاة.")},
        {"Simulation Parameters", QString::fromUtf8(u8"معلمات المحاكاة")},
        {"Total Requests", QString::fromUtf8(u8"إجمالي الطلبات")},
        {"Arrival Rate (req/s)", QString::fromUtf8(u8"معدل الوصول (طلب/ث)")},
        {"Duration (seconds)", QString::fromUtf8(u8"المدة (ثوان)")},
        {"Start Simulation", QString::fromUtf8(u8"بدء المحاكاة")},
        {"Stop", QString::fromUtf8(u8"إيقاف")},
        {"Reset", QString::fromUtf8(u8"إعادة ضبط")},
        {"Runtime Monitor", QString::fromUtf8(u8"مراقبة التشغيل")},
        {"Simulation engine is idle. Configure the parameters and press Start.", QString::fromUtf8(u8"محرك المحاكاة متوقف حاليا. اضبط المعلمات ثم اضغط بدء.")},
        {"Generating and processing requests...", QString::fromUtf8(u8"جار توليد الطلبات ومعالجتها...")},
        {"Simulation stopped by the user.", QString::fromUtf8(u8"أوقف المستخدم المحاكاة.")},
        {"System reset and ready.", QString::fromUtf8(u8"تمت إعادة الضبط والنظام جاهز.")},
        {"Simulation completed successfully.", QString::fromUtf8(u8"اكتملت المحاكاة بنجاح.")},
        {"Configure workers, failures, latency and availability for each infrastructure service.", QString::fromUtf8(u8"اضبط العمال والإخفاقات وزمن الاستجابة والتوفر لكل خدمة في البنية التحتية.")},
        {"Infrastructure Services", QString::fromUtf8(u8"خدمات البنية التحتية")},
        {"Active Workers are calculated automatically: Total Workers - Failed Workers.", QString::fromUtf8(u8"يتم حساب العمال النشطين تلقائيا: إجمالي العمال - العمال المعطلون.")},
        {"Total Workers", QString::fromUtf8(u8"إجمالي العمال")},
        {"Failed Workers", QString::fromUtf8(u8"العمال المعطلون")},
        {"Active Workers", QString::fromUtf8(u8"العمال النشطون")},
        {"Base Latency (ms)", QString::fromUtf8(u8"الاستجابة الأساسية (ms)")},
        {"Failure %", QString::fromUtf8(u8"نسبة الفشل %")},
        {"Available", QString::fromUtf8(u8"متاح")},
        {"Apply Changes", QString::fromUtf8(u8"تطبيق التغييرات")},
        {"Restore Defaults", QString::fromUtf8(u8"استعادة الافتراضي")},
        {"Service configuration is ready.", QString::fromUtf8(u8"إعدادات الخدمات جاهزة.")},
        {"Stop the simulation before changing services.", QString::fromUtf8(u8"أوقف المحاكاة قبل تعديل الخدمات.")},
        {"One of the service controls is missing.", QString::fromUtf8(u8"أحد عناصر التحكم في الخدمة غير موجود.")},
        {"The service configuration could not be updated.", QString::fromUtf8(u8"تعذر تحديث إعدادات الخدمة.")},
        {"✓ Service configuration applied successfully.", QString::fromUtf8(u8"✓ تم تطبيق إعدادات الخدمات بنجاح.")},
        {"Stop the simulation before restoring defaults.", QString::fromUtf8(u8"أوقف المحاكاة قبل استعادة الإعدادات الافتراضية.")},
        {"✓ Default service configuration restored.", QString::fromUtf8(u8"✓ تمت استعادة إعدادات الخدمات الافتراضية.")},
        {"Online", QString::fromUtf8(u8"متصل")},
        {"Offline", QString::fromUtf8(u8"غير متصل")},
        {"ONLINE", QString::fromUtf8(u8"متصل")},
        {"DEGRADED", QString::fromUtf8(u8"متأثر")},
        {"OFFLINE", QString::fromUtf8(u8"متوقف")},
        {"Inject infrastructure faults while the simulation is running and observe their impact in real time.", QString::fromUtf8(u8"احقن أعطالا في البنية التحتية أثناء تشغيل المحاكاة وراقب تأثيرها في الوقت الحقيقي.")},
        {"Fault Control Center", QString::fromUtf8(u8"مركز التحكم بالأعطال")},
        {"Target Service", QString::fromUtf8(u8"الخدمة المستهدفة")},
        {"Select Service", QString::fromUtf8(u8"اختر خدمة")},
        {"Fault Type", QString::fromUtf8(u8"نوع العطل")},
        {"NO ACTIVE FAULT", QString::fromUtf8(u8"لا يوجد عطل نشط")},
        {"Severity", QString::fromUtf8(u8"الشدة")},
        {"Inject Fault", QString::fromUtf8(u8"حقن العطل")},
        {"Recover Service", QString::fromUtf8(u8"استعادة الخدمة")},
        {"Live Fault Log", QString::fromUtf8(u8"سجل الأعطال المباشر")},
        {"Worker Crash", QString::fromUtf8(u8"تعطل العمال")},
        {"Service Down", QString::fromUtf8(u8"توقف الخدمة")},
        {"Slowdown", QString::fromUtf8(u8"تباطؤ")},
        {"Error Spike", QString::fromUtf8(u8"ارتفاع الأخطاء")},
        {"Traffic Spike", QString::fromUtf8(u8"ارتفاع حركة المرور")},
        {"DNS Failure", QString::fromUtf8(u8"فشل DNS")},
        {"TLS Failure", QString::fromUtf8(u8"فشل TLS")},
        {"Memory Pressure", QString::fromUtf8(u8"ضغط الذاكرة")},
        {"Storage Full", QString::fromUtf8(u8"امتلاء التخزين")},
        {"Retry Storm", QString::fromUtf8(u8"عاصفة إعادة المحاولة")},
        {"Link Outage", QString::fromUtf8(u8"انقطاع الرابط")},
        {"No Services", QString::fromUtf8(u8"لا توجد خدمات")},
        {"No service selected.", QString::fromUtf8(u8"لم يتم اختيار خدمة.")},
        {"Workers to Crash", QString::fromUtf8(u8"عدد العمال المراد تعطيلهم")},
        {"Disables worker processes in the selected service and immediately reduces capacity.", QString::fromUtf8(u8"يعطل عمليات العمال في الخدمة المحددة ويخفض السعة مباشرة.")},
        {"Takes the selected service completely offline. Requests reaching it fail immediately.", QString::fromUtf8(u8"يوقف الخدمة المحددة بالكامل، وأي طلب يصل إليها يفشل مباشرة.")},
        {"Latency Multiplier", QString::fromUtf8(u8"مضاعف زمن الاستجابة")},
        {"Multiplies service response time. Example: 2.0x approximately doubles its latency.", QString::fromUtf8(u8"يضاعف زمن استجابة الخدمة. مثال: 2.0x يضاعف زمن الاستجابة تقريبا.")},
        {"Failure Probability", QString::fromUtf8(u8"احتمال الفشل")},
        {"Introduces random application-level request failures in the selected service.", QString::fromUtf8(u8"يضيف حالات فشل عشوائية للطلبات على مستوى التطبيق في الخدمة المحددة.")},
        {"Traffic Multiplier", QString::fromUtf8(u8"مضاعف حركة المرور")},
        {"Simulates a sudden traffic surge. It increases service load, latency, and overload failures.", QString::fromUtf8(u8"يحاكي ارتفاعا مفاجئا في حركة المرور، فيزيد حمل الخدمة وزمن الاستجابة وحالات فشل الحمل الزائد.")},
        {"DNS Failure Probability", QString::fromUtf8(u8"احتمال فشل DNS")},
        {"Simulates DNS resolution failures. For realistic tests, target the Gateway.", QString::fromUtf8(u8"يحاكي فشل حل أسماء DNS. لاختبار واقعي استهدف البوابة.")},
        {"TLS Failure Probability", QString::fromUtf8(u8"احتمال فشل TLS")},
        {"Simulates TLS handshake or certificate failures before a request is processed.", QString::fromUtf8(u8"يحاكي فشل مصافحة TLS أو الشهادة قبل معالجة الطلب.")},
        {"Simulates memory pressure. Higher values increase latency and can introduce request failures.", QString::fromUtf8(u8"يحاكي ضغط الذاكرة. القيم الأعلى تزيد زمن الاستجابة وقد تسبب فشل الطلبات.")},
        {"Storage Pressure", QString::fromUtf8(u8"ضغط التخزين")},
        {"Simulates storage exhaustion. For realistic tests, target the Database.", QString::fromUtf8(u8"يحاكي نفاد مساحة التخزين. لاختبار واقعي استهدف قاعدة البيانات.")},
        {"Retry Multiplier", QString::fromUtf8(u8"مضاعف إعادة المحاولة")},
        {"Simulates clients repeatedly retrying failed requests, increasing effective load and latency.", QString::fromUtf8(u8"يحاكي إعادة العملاء للطلبات الفاشلة بشكل متكرر، مما يزيد الحمل الفعلي وزمن الاستجابة.")},
        {"Link Failure Probability", QString::fromUtf8(u8"احتمال فشل الرابط")},
        {"Simulates an unstable or partially unavailable network link to the selected service.", QString::fromUtf8(u8"يحاكي رابط شبكة غير مستقر أو متاح جزئيا للخدمة المحددة.")},
        {"Live topology of the simulated request path. Node colors and metrics update automatically when services are changed, faults are injected, or services recover.", QString::fromUtf8(u8"عرض حي لمسار الطلبات المحاكى. تتحدث ألوان العقد والمؤشرات تلقائيا عند تعديل الخدمات أو حقن الأعطال أو استعادة الخدمات.")},
        {"Client Request Flow", QString::fromUtf8(u8"مسار طلب العميل")},
        {"Client", QString::fromUtf8(u8"العميل")},
        {"Gateway", QString::fromUtf8(u8"البوابة")},
        {"Web Server", QString::fromUtf8(u8"خادم الويب")},
        {"Application API", QString::fromUtf8(u8"واجهة التطبيق")},
        {"Database", QString::fromUtf8(u8"قاعدة البيانات")},
        {"Clear History", QString::fromUtf8(u8"مسح السجل")},
        {"Delete all saved simulation runs?", QString::fromUtf8(u8"هل تريد حذف جميع تشغيلات المحاكاة المحفوظة؟")},
        {"This permanently removes all locally saved SQLite history. Previously exported PNG, JPG and PDF reports are not deleted.", QString::fromUtf8(u8"سيؤدي هذا إلى حذف سجل SQLite المحلي نهائيا. التقارير المصدرة سابقا بصيغ PNG وJPG وPDF لن يتم حذفها.")},
        {"Cancel", QString::fromUtf8(u8"إلغاء")},
        {"Delete All", QString::fromUtf8(u8"حذف الكل")},
        {"Saved simulation runs stored locally in SQLite. Select any run to open its complete report.", QString::fromUtf8(u8"تشغيلات المحاكاة المحفوظة محليا في SQLite. اختر أي تشغيل لفتح تقريره الكامل.")},
        {"Simulation Runs", QString::fromUtf8(u8"تشغيلات المحاكاة")},
        {"Open Report", QString::fromUtf8(u8"فتح التقرير")},
        {"Open the selected saved run in Reports", QString::fromUtf8(u8"افتح التشغيل المحفوظ المحدد في صفحة التقارير")},
        {"Refresh", QString::fromUtf8(u8"تحديث")},
        {"History is ready.", QString::fromUtf8(u8"السجل جاهز.")},
        {"Run", QString::fromUtf8(u8"التشغيل")},
        {"Date / Time", QString::fromUtf8(u8"التاريخ / الوقت")},
        {"Total", QString::fromUtf8(u8"الإجمالي")},
        {"Processed", QString::fromUtf8(u8"المعالجة")},
        {"Successful", QString::fromUtf8(u8"الناجحة")},
        {"Failed", QString::fromUtf8(u8"الفاشلة")},
        {"Success Rate", QString::fromUtf8(u8"نسبة النجاح")},
        {"Avg. Latency", QString::fromUtf8(u8"متوسط زمن الاستجابة")},
        {"History is already empty.", QString::fromUtf8(u8"السجل فارغ بالفعل.")},
        {"No completed run", QString::fromUtf8(u8"لا يوجد تشغيل مكتمل")},
        {"History was cleared. Complete a simulation to create a new report.", QString::fromUtf8(u8"تم مسح السجل. أكمل محاكاة لإنشاء تقرير جديد.")},
        {"No saved simulation runs yet. Complete a simulation to create the first record.", QString::fromUtf8(u8"لا توجد تشغيلات محاكاة محفوظة بعد. أكمل محاكاة لإنشاء أول سجل.")},
        {"Select a simulation run first.", QString::fromUtf8(u8"اختر تشغيل محاكاة أولا.")},
        {"The selected run could not be read.", QString::fromUtf8(u8"تعذر قراءة التشغيل المحدد.")},
        {"Reports page could not be opened.", QString::fromUtf8(u8"تعذر فتح صفحة التقارير.")},
        {"Reports panel could not be found.", QString::fromUtf8(u8"تعذر العثور على لوحة التقارير.")},
        {"Generate a professional simulation report with fault and service-health details.", QString::fromUtf8(u8"أنشئ تقرير محاكاة احترافيا يتضمن تفاصيل الأعطال وحالة الخدمات.")},
        {"Simulation Report", QString::fromUtf8(u8"تقرير المحاكاة")},
        {"ATHAR", QString::fromUtf8(u8"أثر")},
        {"FAULT LAB 2", QString::fromUtf8(u8"مختبر الأعطال 2")},
        {"ATHAR FAULT LAB 2", QString::fromUtf8(u8"أثر — مختبر الأعطال 2")},
        {"No completed simulation selected.", QString::fromUtf8(u8"لم يتم تحديد محاكاة مكتملة.")},
        {"Run Number", QString::fromUtf8(u8"رقم التشغيل")},
        {"Fault Summary", QString::fromUtf8(u8"ملخص الأعطال")},
        {"No active faults.", QString::fromUtf8(u8"لا توجد أعطال نشطة.")},
        {"Service Health", QString::fromUtf8(u8"حالة الخدمات")},
        {"No service-health data.", QString::fromUtf8(u8"لا توجد بيانات عن حالة الخدمات.")},
        {"Notes", QString::fromUtf8(u8"ملاحظات")},
        {"NOTES", QString::fromUtf8(u8"ملاحظات")},
        {"No additional notes.", QString::fromUtf8(u8"لا توجد ملاحظات إضافية.")},
        {"Export report", QString::fromUtf8(u8"تصدير التقرير")},
        {"Export PNG", QString::fromUtf8(u8"تصدير PNG")},
        {"Export JPG", QString::fromUtf8(u8"تصدير JPG")},
        {"Export PDF", QString::fromUtf8(u8"تصدير PDF")},
        {"Ready to export this report.", QString::fromUtf8(u8"التقرير جاهز للتصدير.")},
        {"Complete a simulation first.", QString::fromUtf8(u8"أكمل محاكاة أولا.")},
        {"No active faults at simulation completion.", QString::fromUtf8(u8"لا توجد أعطال نشطة عند اكتمال المحاكاة.")},
        {"No report data.", QString::fromUtf8(u8"لا توجد بيانات تقرير.")},
        {"Complete a simulation before exporting.", QString::fromUtf8(u8"أكمل محاكاة قبل التصدير.")},
        {"Unknown Service", QString::fromUtf8(u8"خدمة غير معروفة")},
        {"There is no completed simulation report to export.", QString::fromUtf8(u8"لا يوجد تقرير محاكاة مكتمل لتصديره.")},
        {"Save Report as PDF", QString::fromUtf8(u8"حفظ التقرير بصيغة PDF")},
        {"PDF export failed. The destination file could not be created.", QString::fromUtf8(u8"فشل تصدير PDF. تعذر إنشاء الملف في الوجهة المحددة.")},
        {"PDF export failed.", QString::fromUtf8(u8"فشل تصدير PDF.")},
        {"Simulation Analysis Report", QString::fromUtf8(u8"تقرير تحليل المحاكاة")},
        {"Simulation Metrics", QString::fromUtf8(u8"مؤشرات المحاكاة")},
        {"TOTAL REQUESTS", QString::fromUtf8(u8"إجمالي الطلبات")},
        {"PROCESSED", QString::fromUtf8(u8"المعالجة")},
        {"SUCCESSFUL", QString::fromUtf8(u8"الناجحة")},
        {"FAILED", QString::fromUtf8(u8"الفاشلة")},
        {"Live Performance", QString::fromUtf8(u8"الأداء المباشر")},
        {"Runtime request outcome and average latency during the current simulation.", QString::fromUtf8(u8"نتيجة الطلبات أثناء التشغيل ومتوسط زمن الاستجابة خلال المحاكاة الحالية.")},
        {"REQUEST OUTCOME", QString::fromUtf8(u8"نتيجة الطلبات")},
        {"Runtime Fail", QString::fromUtf8(u8"فشل التشغيل")},
        {"Start a simulation to populate the chart.", QString::fromUtf8(u8"ابدأ محاكاة لعرض البيانات في الرسم البياني.")},
        {"AVERAGE LATENCY", QString::fromUtf8(u8"متوسط زمن الاستجابة")},
        {"Latency ms", QString::fromUtf8(u8"زمن الاستجابة ms")},
        {"Decrease", QString::fromUtf8(u8"إنقاص")},
        {"Increase", QString::fromUtf8(u8"زيادة")},
        {"Made by:", QString::fromUtf8(u8"إعداد:")},
        {"Version 2.0", QString::fromUtf8(u8"الإصدار 2.0")},
        {"None", QString::fromUtf8(u8"لا يوجد")},
        {"History Error", QString::fromUtf8(u8"خطأ في السجل")},
        {"History Database", QString::fromUtf8(u8"قاعدة بيانات السجل")},
        {"Athar Fault Lab 2\nVersion 2.0\n\nMade by:\nabdulaziz alyousef", QString::fromUtf8(u8"أثر — مختبر الأعطال 2\nالإصدار 2.0\n\nإعداد:\nabdulaziz alyousef")},
        {"Athar Fault Lab 2 | Made by abdulaziz alyousef", QString::fromUtf8(u8"أثر — مختبر الأعطال 2 | إعداد: abdulaziz alyousef")}
    };

    return values;
}

inline QString text(const QString &source)
{
    if (!isArabic())
    {
        return source;
    }

    const auto &values = dictionary();
    auto found = values.constFind(source);

    if (found != values.cend())
    {
        return found.value();
    }

    QString result = source;

    const QList<QPair<QString, QString>> replacements = {
        {"Selected historical run #", QString::fromUtf8(u8"التشغيل التاريخي المحدد #")},
        {"from SQLite History", QString::fromUtf8(u8"من سجل SQLite")},
        {"Save Report as ", QString::fromUtf8(u8"حفظ التقرير بصيغة ")},
        {"report saved successfully:", QString::fromUtf8(u8"تم حفظ التقرير بنجاح:")},
        {"export failed.", QString::fromUtf8(u8"فشل التصدير.")},
        {"Version 2.0", QString::fromUtf8(u8"الإصدار 2.0")},
        {"Made by:", QString::fromUtf8(u8"إعداد:")},
        {"DEGRADED", QString::fromUtf8(u8"متأثر")},
        {"ONLINE", QString::fromUtf8(u8"متصل")},
        {"OFFLINE", QString::fromUtf8(u8"متوقف")},
        {"Latest completed run #", QString::fromUtf8(u8"أحدث تشغيل مكتمل #")},
        {"Loaded from SQLite History.", QString::fromUtf8(u8"تم التحميل من سجل SQLite.")},
        {"is the latest completed simulation.", QString::fromUtf8(u8"هو أحدث تشغيل محاكاة مكتمل.")},
        {"was selected manually from History.", QString::fromUtf8(u8"تم اختياره يدويا من السجل.")},
        {"Loaded ", QString::fromUtf8(u8"تم تحميل ")},
        {"saved simulation run(s). Select a row to inspect its report.", QString::fromUtf8(u8" تشغيلات محاكاة محفوظة. اختر صفا لعرض تقريره.")},
        {"selected. Press Open Report or double-click the row.", QString::fromUtf8(u8"محدد. اضغط فتح التقرير أو انقر نقرا مزدوجا على الصف.")},
        {"History could not be cleared:", QString::fromUtf8(u8"تعذر مسح السجل:")},
        {"Configured Failure", QString::fromUtf8(u8"الفشل المضبوط")},
        {"Effective Failure", QString::fromUtf8(u8"الفشل الفعلي")},
        {"Failed Workers", QString::fromUtf8(u8"العمال المعطلون")},
        {"Active Workers", QString::fromUtf8(u8"العمال النشطون")},
        {"Total Workers", QString::fromUtf8(u8"إجمالي العمال")},
        {"Workers to Crash", QString::fromUtf8(u8"عدد العمال المراد تعطيلهم")},
        {"Application API", QString::fromUtf8(u8"واجهة التطبيق")},
        {"Web Server", QString::fromUtf8(u8"خادم الويب")},
        {"Gateway", QString::fromUtf8(u8"البوابة")},
        {"Database", QString::fromUtf8(u8"قاعدة البيانات")},
        {"Worker Crash", QString::fromUtf8(u8"تعطل العمال")},
        {"Service Down", QString::fromUtf8(u8"توقف الخدمة")},
        {"Traffic Spike", QString::fromUtf8(u8"ارتفاع حركة المرور")},
        {"Error Spike", QString::fromUtf8(u8"ارتفاع الأخطاء")},
        {"DNS Failure", QString::fromUtf8(u8"فشل DNS")},
        {"TLS Failure", QString::fromUtf8(u8"فشل TLS")},
        {"Memory Pressure", QString::fromUtf8(u8"ضغط الذاكرة")},
        {"Storage Full", QString::fromUtf8(u8"امتلاء التخزين")},
        {"Retry Storm", QString::fromUtf8(u8"عاصفة إعادة المحاولة")},
        {"Link Outage", QString::fromUtf8(u8"انقطاع الرابط")},
        {"Slowdown", QString::fromUtf8(u8"تباطؤ")},
        {"Active Fault:", QString::fromUtf8(u8"العطل النشط:")},
        {"ACTIVE FAULT:", QString::fromUtf8(u8"العطل النشط:")},
        {"Base Latency:", QString::fromUtf8(u8"زمن الاستجابة الأساسي:")},
        {"Latency:", QString::fromUtf8(u8"زمن الاستجابة:")},
        {"Failure:", QString::fromUtf8(u8"الفشل:")},
        {"Workers:", QString::fromUtf8(u8"العمال:")},
        {"Workers ", QString::fromUtf8(u8"العمال ")},
        {"Failed Workers:", QString::fromUtf8(u8"العمال المعطلون:")},
        {"Failed:", QString::fromUtf8(u8"الفاشلة:")},
        {"Successful:", QString::fromUtf8(u8"الناجحة:")},
        {"Processed:", QString::fromUtf8(u8"المعالجة:")},
        {"Run #", QString::fromUtf8(u8"التشغيل #")},
        {" RUNS", QString::fromUtf8(u8" تشغيلات")},
        {"RECOVERED", QString::fromUtf8(u8"تمت الاستعادة")},
        {"FAULT", QString::fromUtf8(u8"عطل")},
        {"ERROR", QString::fromUtf8(u8"خطأ")},
        {"No target service selected.", QString::fromUtf8(u8"لم يتم اختيار خدمة مستهدفة.")},
        {"Fault injection failed.", QString::fromUtf8(u8"فشل حقن العطل.")},
        {"Service recovery failed.", QString::fromUtf8(u8"فشلت استعادة الخدمة.")},
        {"active", QString::fromUtf8(u8"نشط")},
        {"Failed", QString::fromUtf8(u8"معطل")},
        {"Failure", QString::fromUtf8(u8"فشل")},
        {"Latency", QString::fromUtf8(u8"زمن الاستجابة")},
        {"Fault", QString::fromUtf8(u8"العطل")},
        {"None", QString::fromUtf8(u8"لا يوجد")}
    };

    for (const auto &replacement : replacements)
    {
        result.replace(
            replacement.first,
            replacement.second,
            Qt::CaseSensitive
        );
    }

    return result;
}

inline void initialize()
{
    if (!qApp)
    {
        return;
    }

    QSettings settings;
    const QString language =
        settings.value(
            "appearance/language",
            "en"
        ).toString();

    qApp->setProperty(
        "atharLanguage",
        language == "ar" ? "ar" : "en"
    );

    qApp->setLayoutDirection(
        language == "ar"
            ? Qt::RightToLeft
            : Qt::LeftToRight
    );
}

inline void setArabic(bool enabled)
{
    if (!qApp)
    {
        return;
    }

    const QString language =
        enabled ? "ar" : "en";

    qApp->setProperty(
        "atharLanguage",
        language
    );

    qApp->setLayoutDirection(
        enabled
            ? Qt::RightToLeft
            : Qt::LeftToRight
    );

    QSettings settings;
    settings.setValue(
        "appearance/language",
        language
    );
}

inline void refreshQObjectText(
    QObject *object,
    const std::function<QString()> &getter,
    const std::function<void(const QString &)> &setter
)
{
    if (!object)
    {
        return;
    }

    static const char sourceProperty[] =
        "_atharEnglishSource";

    static const char appliedProperty[] =
        "_atharLastApplied";

    QString current = getter();
    QVariant sourceVariant =
        object->property(sourceProperty);

    QString source =
        sourceVariant.isValid()
            ? sourceVariant.toString()
            : QString();

    QString lastApplied =
        object->property(
            appliedProperty
        ).toString();

    if (
        !sourceVariant.isValid() ||
        current != lastApplied
    )
    {
        source = current;
        object->setProperty(
            sourceProperty,
            source
        );
    }

    QString desired =
        isArabic()
            ? text(source)
            : source;

    if (current != desired)
    {
        setter(desired);
    }

    object->setProperty(
        appliedProperty,
        desired
    );
}

inline void refreshTableItem(
    QTableWidgetItem *item
)
{
    if (!item)
    {
        return;
    }

    constexpr int sourceRole =
        Qt::UserRole + 701;

    constexpr int appliedRole =
        Qt::UserRole + 702;

    QString current = item->text();
    QVariant sourceVariant =
        item->data(sourceRole);

    QString source =
        sourceVariant.isValid()
            ? sourceVariant.toString()
            : QString();

    QString lastApplied =
        item->data(
            appliedRole
        ).toString();

    if (
        !sourceVariant.isValid() ||
        current != lastApplied
    )
    {
        source = current;
        item->setData(
            sourceRole,
            source
        );
    }

    QString desired =
        isArabic()
            ? text(source)
            : source;

    if (current != desired)
    {
        item->setText(desired);
    }

    item->setData(
        appliedRole,
        desired
    );
}

inline void refreshListItem(
    QListWidgetItem *item
)
{
    if (!item)
    {
        return;
    }

    constexpr int sourceRole =
        Qt::UserRole + 711;

    constexpr int appliedRole =
        Qt::UserRole + 712;

    QString current = item->text();
    QVariant sourceVariant =
        item->data(sourceRole);

    QString source =
        sourceVariant.isValid()
            ? sourceVariant.toString()
            : QString();

    QString lastApplied =
        item->data(
            appliedRole
        ).toString();

    if (
        !sourceVariant.isValid() ||
        current != lastApplied
    )
    {
        source = current;
        item->setData(
            sourceRole,
            source
        );
    }

    QString desired =
        isArabic()
            ? text(source)
            : source;

    if (current != desired)
    {
        item->setText(desired);
    }

    item->setData(
        appliedRole,
        desired
    );
}

inline void refreshApplication()
{
    if (!qApp)
    {
        return;
    }

    const auto widgets = qApp->allWidgets();

    for (QWidget *widget : widgets)
    {
        if (!widget)
        {
            continue;
        }

        if (QLabel *label =
                qobject_cast<QLabel *>(widget))
        {
            refreshQObjectText(
                label,
                [label]()
                {
                    return label->text();
                },
                [label](const QString &value)
                {
                    label->setText(value);
                }
            );
        }
        else if (QAbstractButton *button =
                     qobject_cast<QAbstractButton *>(widget))
        {
            refreshQObjectText(
                button,
                [button]()
                {
                    return button->text();
                },
                [button](const QString &value)
                {
                    button->setText(value);
                }
            );
        }
        else if (QGroupBox *groupBox =
                     qobject_cast<QGroupBox *>(widget))
        {
            refreshQObjectText(
                groupBox,
                [groupBox]()
                {
                    return groupBox->title();
                },
                [groupBox](const QString &value)
                {
                    groupBox->setTitle(value);
                }
            );
        }

        if (QTableWidget *table =
                qobject_cast<QTableWidget *>(widget))
        {
            for (
                int column = 0;
                column < table->columnCount();
                ++column
            )
            {
                refreshTableItem(
                    table->horizontalHeaderItem(
                        column
                    )
                );
            }

            for (
                int row = 0;
                row < table->rowCount();
                ++row
            )
            {
                for (
                    int column = 0;
                    column < table->columnCount();
                    ++column
                )
                {
                    refreshTableItem(
                        table->item(
                            row,
                            column
                        )
                    );
                }
            }
        }

        if (QListWidget *list =
                qobject_cast<QListWidget *>(widget))
        {
            for (
                int index = 0;
                index < list->count();
                ++index
            )
            {
                refreshListItem(
                    list->item(index)
                );
            }
        }

        if (QComboBox *combo =
                qobject_cast<QComboBox *>(widget))
        {
            constexpr int sourceRole =
                Qt::UserRole + 721;

            constexpr int appliedRole =
                Qt::UserRole + 722;

            for (
                int index = 0;
                index < combo->count();
                ++index
            )
            {
                QString current =
                    combo->itemText(index);

                QVariant sourceVariant =
                    combo->itemData(
                        index,
                        sourceRole
                    );

                QString source =
                    sourceVariant.isValid()
                        ? sourceVariant.toString()
                        : QString();

                QString lastApplied =
                    combo->itemData(
                        index,
                        appliedRole
                    ).toString();

                if (
                    !sourceVariant.isValid() ||
                    current != lastApplied
                )
                {
                    source = current;
                    combo->setItemData(
                        index,
                        source,
                        sourceRole
                    );
                }

                QString desired =
                    isArabic()
                        ? text(source)
                        : source;

                if (current != desired)
                {
                    combo->setItemText(
                        index,
                        desired
                    );
                }

                combo->setItemData(
                    index,
                    desired,
                    appliedRole
                );
            }
        }

        if (QMenu *menu =
                qobject_cast<QMenu *>(widget))
        {
            for (QAction *action : menu->actions())
            {
                if (!action)
                {
                    continue;
                }

                refreshQObjectText(
                    action,
                    [action]()
                    {
                        return action->text();
                    },
                    [action](const QString &value)
                    {
                        action->setText(value);
                    }
                );
            }
        }
    }
}
}

#endif

