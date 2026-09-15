# Athar Fault Lab 2 | أثر العطل 2

<div align="center">

**مختبر محاكاة أعطال البنية التحتية للمواقع — Website Fault Simulation Laboratory**

A native Windows simulation laboratory for studying how website infrastructure behaves under failures, overload, degraded services, and abnormal operating conditions.

**Built with C++17, Qt Widgets, CMake, and SQLite**

Made by **abdulaziz alyousef**

</div>

---

## العربية

### نظرة عامة

**Athar Fault Lab 2 | أثر العطل 2** هو برنامج محاكاة مكتبي لنظام Windows تم تطويره بلغة **C++** باستخدام إطار العمل **Qt Widgets**، ويهدف إلى محاكاة بنية تحتية مبسطة لموقع إلكتروني ودراسة أثر الأعطال المختلفة على الخدمات، الطلبات، زمن الاستجابة، معدل النجاح، ومؤشرات الأداء العامة.

البرنامج لا يقوم بإرسال هجمات أو طلبات حقيقية إلى مواقع خارجية، ولا يعتمد على الاتصال بخوادم فعلية. جميع العمليات تتم داخل بيئة محاكاة محلية لأغراض تعليمية وتجريبية، بحيث يستطيع المستخدم تشغيل النظام، تغيير إعدادات الخدمات، حقن أعطال مختلفة، مراقبة أثرها لحظيًا، ثم مراجعة النتائج وحفظها وتصدير تقارير عنها.

تم تصميم المشروع كنسخة C++/Qt متقدمة من فكرة مختبر أعطال، مع واجهة رسومية أصلية لنظام Windows، دعم العربية والإنجليزية، وضعين داكن وفاتح، تخزين نتائج التشغيل في SQLite، تقارير قابلة للتصدير، وعرض حي لحالة البنية التحتية.

---

## فكرة المشروع

الفكرة الأساسية هي تمثيل مسار طلب المستخدم داخل موقع إلكتروني عبر سلسلة من الخدمات:

```text
Client
  ↓
Gateway
  ↓
Web Server
  ↓
Application API
  ↓
Database
```

كل طلب يدخل إلى النظام ويمر عبر الخدمات بالتسلسل. لكل خدمة خصائص مثل:

- عدد العمال المتاحين Workers
- زمن الاستجابة الأساسي
- نسبة الفشل
- حالة الخدمة
- أثر الأعطال الحالية
- قدرة الخدمة على استقبال ومعالجة الطلبات

أثناء المحاكاة يمكن أن تكون البنية التحتية في حالة طبيعية، أو تتعرض إلى أعطال تؤدي إلى بطء، توقف، رفض طلبات، ضغط زائد، أو ارتفاع في نسبة الأخطاء.

الهدف هو إظهار كيف ينتقل أثر العطل من خدمة واحدة إلى بقية النظام وكيف تتغير مؤشرات الأداء نتيجة لذلك.

---

## أهداف المشروع

تم إنشاء Athar Fault Lab 2 لتحقيق عدة أهداف تقنية وتعليمية:

- تقديم محاكاة مبسطة لمفاهيم الاعتمادية والمرونة في أنظمة الويب.
- دراسة أثر الأعطال على الخدمات والطلبات.
- توضيح العلاقة بين زمن الاستجابة، عدد العمال، الفشل، والضغط.
- تجربة Fault Injection داخل بيئة آمنة ومحلية.
- مراقبة النظام أثناء التشغيل من خلال مؤشرات ورسومات حية.
- تخزين النتائج السابقة والعودة إليها لاحقًا.
- إنشاء تقارير قابلة للحفظ بصيغ مختلفة.
- تقديم واجهة ثنائية اللغة بالعربية والإنجليزية.
- بناء تطبيق Windows أصلي باستخدام C++ وQt بدلاً من تطبيق ويب.

---

## المزايا الرئيسية

### 1. لوحة المعلومات Dashboard

تعرض لوحة المعلومات حالة النظام بشكل سريع ومباشر، وتشمل مؤشرات ورسومات تساعد على فهم ما يحدث أثناء المحاكاة.

يمكن من خلالها متابعة مؤشرات مثل:

- حالة البنية التحتية
- إجمالي الطلبات
- الطلبات الناجحة
- الطلبات الفاشلة
- زمن الاستجابة
- معدل الفشل
- التغير في الأداء أثناء التشغيل
- حالة الخدمات

تم تصميم الرسومات باستخدام QPainter لتكون جزءًا من التطبيق نفسه بدون الحاجة إلى مكتبات رسم خارجية.

---

### 2. صفحة المحاكاة Simulation

تسمح صفحة المحاكاة بالتحكم في التشغيل الأساسي للنظام.

الإعدادات الرئيسية تشمل:

- إجمالي عدد الطلبات
- معدل وصول الطلبات
- مدة التشغيل
- تشغيل المحاكاة
- إيقاف المحاكاة
- إعادة ضبط المحاكاة
- متابعة التقدم
- مشاهدة حالة التشغيل الحالية

تقوم المحاكاة بإنشاء طلبات افتراضية تمر عبر الخدمات الداخلية، ويتم حساب النتائج اعتمادًا على إعدادات كل خدمة والأعطال النشطة.

---

### 3. إدارة الخدمات Services

يحتوي النظام على أربع خدمات أساسية:

| الخدمة | الوصف |
|---|---|
| Gateway | نقطة دخول الطلبات إلى البنية التحتية |
| Web Server | طبقة الويب التي تستقبل الطلب بعد البوابة |
| Application API | طبقة منطق التطبيق والعمليات |
| Database | طبقة قاعدة البيانات |

يمكن تعديل إعدادات كل خدمة مثل:

- Total Workers
- Failed Workers
- Active Workers
- Base Latency
- Failure Rate
- Available Workers

كما يمكن تطبيق الإعدادات الجديدة أو استعادة القيم الافتراضية.

الإعدادات الافتراضية للمشروع:

| Service | Workers | Base Latency |
|---|---:|---:|
| Gateway | 12 | 4 ms |
| Web Server | 8 | 12 ms |
| Application API | 8 | 18 ms |
| Database | 8 | 25 ms |

---

## الأعطال المدعومة

يحتوي Athar Fault Lab 2 على مجموعة من الأعطال القابلة للحقن داخل النظام.

### Worker Crash
يحاكي تعطل جزء من العمال داخل خدمة معينة، مما يقلل القدرة المتاحة على معالجة الطلبات.

### Service Down
يحاكي توقف خدمة بالكامل، بحيث تصبح غير قادرة على تنفيذ الطلبات التي تصل إليها.

### Slowdown
يزيد زمن معالجة الطلبات داخل الخدمة، ويحاكي حالة البطء أو انخفاض الأداء.

### Error Spike
يرفع نسبة الأخطاء بشكل مؤقت، ويستخدم لمحاكاة ارتفاع مفاجئ في فشل الطلبات.

### Traffic Spike
يزيد الضغط على النظام عبر ارتفاع معدل الطلبات، مما يسمح بدراسة أثر الحمل العالي.

### DNS Failure
يحاكي فشلًا في مرحلة دخول الطلب إلى النظام، بحيث قد لا يتمكن بعض العملاء من الوصول إلى البنية التحتية.

### TLS Failure
يحاكي فشل الاتصال في مرحلة التهيئة الآمنة قبل وصول الطلب إلى الخدمات الداخلية.

### Memory Pressure
يحاكي ضغط الذاكرة وتأثيره على قدرة الخدمة والأداء.

### Storage Full
يحاكي امتلاء التخزين وتأثيره على العمليات التي تحتاج إلى الكتابة أو الحفظ.

### Retry Storm
يحاكي زيادة الضغط الناتجة عن إعادة المحاولة المتكررة بعد الفشل، وهو سيناريو قد يؤدي إلى تضخيم المشكلة بدلًا من حلها.

### Link Outage
يحاكي انقطاع الاتصال بين مكونات البنية التحتية وتأثيره على استمرار مرور الطلبات.

---

## Network View

تعرض صفحة Network View البنية التحتية للموقع بصريًا:

```text
Client → Gateway → Web Server → Application API → Database
```

ويتم إظهار حالة كل جزء من النظام باستخدام حالات تشغيل واضحة مثل:

- ONLINE
- DEGRADED
- OFFLINE

كما تعرض الصفحة معلومات مرتبطة بالخدمات مثل:

- عدد العمال
- زمن الاستجابة
- نسبة الفشل
- العطل النشط
- حالة الخدمة

---

## سجل التشغيل History

يستخدم البرنامج قاعدة بيانات **SQLite** محلية لحفظ نتائج عمليات المحاكاة السابقة.

قاعدة البيانات تُنشأ أثناء الاستخدام داخل:

```text
data/athar_history.db
```

يستطيع المستخدم من صفحة History:

- مراجعة عمليات المحاكاة السابقة
- مشاهدة وقت وتاريخ التشغيل
- مراجعة الإعدادات والنتائج
- اختيار تشغيل سابق
- استخدام تشغيل سابق في التقارير
- مسح السجلات عند الحاجة

ملف قاعدة البيانات Runtime Data ولا يتم تضمينه ضمن السورس في GitHub.

---

## التقارير Reports

يدعم البرنامج إنشاء تقارير من نتائج المحاكاة الحالية أو من تشغيل سابق محفوظ.

صيغ التصدير المدعومة:

- PNG
- JPG
- PDF

يتبع التقرير الثيم الحالي للتطبيق، لذلك يمكن إنتاج تقرير مناسب للوضع الداكن أو الفاتح.

---

## دعم العربية والإنجليزية

يدعم Athar Fault Lab 2 واجهتين:

- العربية
- English

يمكن التبديل بين اللغتين من داخل التطبيق.

عند اختيار العربية يتم تطبيق اتجاه RTL على الواجهة المناسبة، بينما تستخدم الإنجليزية اتجاه LTR.

يقوم النظام بتحديث النصوص والعناوين والقوائم وعناصر الجداول تلقائيًا عند تغيير اللغة.

---

## الوضع الداكن والفاتح

يدعم البرنامج:

- Dark Theme
- Light Theme

ويتم حفظ اختيار المستخدم باستخدام QSettings، لذلك يحتفظ البرنامج بالثيم المختار عند التشغيل التالي.

---

## شاشة البداية Splash Screen

عند تشغيل البرنامج تظهر شاشة بداية مخصصة باسم المشروع، ثم تنتقل إلى النافذة الرئيسية باستخدام تأثير Fade.

تتبع شاشة البداية الثيم المختار مسبقًا للمستخدم.

---

## آلية المحاكاة

يمر الطلب الافتراضي بعدة مراحل:

```text
Request Created
      ↓
Gateway
      ↓
Web Server
      ↓
Application API
      ↓
Database
      ↓
Result
```

في كل خدمة يتم أخذ مجموعة من العوامل في الاعتبار، مثل:

- عدد العمال المتاحين
- زمن الاستجابة الأساسي
- نسبة الفشل
- العطل النشط
- حالة الخدمة
- الحمل الحالي

إذا فشل الطلب في إحدى المراحل، يمكن أن يتوقف قبل الوصول إلى المراحل التالية.

أما إذا نجح، فيستمر حتى نهاية المسار ويتم احتسابه ضمن الطلبات الناجحة.

---

## الفرق بين Fault Probability و Runtime Failure

يفرق البرنامج بين الإعداد النظري للفشل وبين النتيجة التي ظهرت فعليًا أثناء التشغيل.

إذا تم ضبط Failure Rate على قيمة معينة فهذا لا يعني بالضرورة أن نسبة النتائج الفعلية ستكون مطابقة حرفيًا، لأن المحاكاة تعتمد على الاحتمالات وتوزيع الطلبات أثناء التشغيل.

---

## البنية التقنية

تم تطوير المشروع باستخدام:

- **C++17**
- **Qt Widgets**
- **CMake**
- **SQLite**
- **Qt SQL**
- **QSettings**
- **QPainter**
- **Windows Resource File**
- **Windows DWM API**

وعلى Windows يتم ربط التطبيق أيضًا بمكتبة:

```text
dwmapi
```

---

## هيكل المشروع

```text
Athar-Fault-Lab-2/
│
├── CMakeLists.txt
├── .gitignore
│
├── resources/
│   ├── athar.ico
│   └── athar.rc
│
└── src/
    ├── main.cpp
    ├── simulation/
    │   ├── Fault.cpp
    │   ├── Fault.h
    │   ├── Service.cpp
    │   ├── Service.h
    │   ├── SimulationEngine.cpp
    │   └── SimulationEngine.h
    ├── storage/
    │   ├── HistoryManager.cpp
    │   └── HistoryManager.h
    └── ui/
        ├── MainWindow.cpp
        ├── MainWindow.h
        ├── SplashScreen.cpp
        ├── SplashScreen.h
        ├── Dashboard.cpp
        ├── Dashboard.h
        ├── FaultPanel.cpp
        ├── FaultPanel.h
        ├── MetricsPanel.cpp
        ├── MetricsPanel.h
        ├── NetworkView.cpp
        ├── NetworkView.h
        ├── HistoryPanel.cpp
        ├── HistoryPanel.h
        ├── ReportsPanel.cpp
        ├── ReportsPanel.h
        └── UiLanguage.h
```

---

## شرح المكونات الرئيسية

### `main.cpp`
نقطة تشغيل البرنامج ومسؤول عن QApplication، بيانات التطبيق، الثيم، Splash Screen، وإنشاء MainWindow.

### `SimulationEngine`
المحرك المسؤول عن منطق المحاكاة وتشغيل الطلبات وحساب النتائج.

### `Service`
يمثل خدمة داخل البنية التحتية ويحتوي على إعداداتها.

### `Fault`
يمثل أنواع الأعطال وآثارها.

### `HistoryManager`
مسؤول عن SQLite وحفظ واسترجاع نتائج المحاكاة.

### `MainWindow`
النافذة الرئيسية التي تربط الصفحات والإعدادات العامة واللغة والثيم.

### `Dashboard`
تعرض ملخص حالة النظام ومؤشرات الأداء.

### `FaultPanel`
واجهة التحكم في Fault Injection.

### `MetricsPanel`
مسؤولة عن عرض مؤشرات المحاكاة.

### `NetworkView`
تعرض المسار البصري للخدمات وحالة كل خدمة.

### `HistoryPanel`
تعرض سجلات المحاكاة السابقة.

### `ReportsPanel`
مسؤولة عن عرض وتصدير التقارير.

### `UiLanguage.h`
يحتوي على نظام الترجمة الداخلي للعربية والإنجليزية.

---

## البناء من المصدر

### المتطلبات

- Windows
- CMake 3.21 أو أحدث
- مترجم يدعم C++17
- Qt Widgets
- Qt SQL

تم اختبار المشروع باستخدام:

### Windows x64
```text
Qt 6.11.2
MSVC 2022 64-bit
```

### Windows x86
```text
Qt 5.15.2
MinGW 32-bit
```

### البناء باستخدام Qt Creator

1. افتح `CMakeLists.txt`.
2. اختر Kit المناسب.
3. اختر Release.
4. نفذ Configure.
5. نفذ Build.
6. الملف التنفيذي النهائي:

```text
Athar Fault Lab 2.exe
```

---

## تحميل النسخ الجاهزة

تتوفر النسخ الجاهزة من صفحة **Releases**.

### Windows x64
```text
Athar-Fault-Lab-2-v2.0-Windows-x64.zip
```

موصى بها لأجهزة Windows الحديثة 64-bit.

### Windows x86
```text
Athar-Fault-Lab-2-v2.0-Windows-x86.zip
```

مخصصة لبيئات Windows 32-bit.

بعد التحميل:

1. فك ضغط ZIP.
2. افتح المجلد الناتج.
3. شغّل `Athar Fault Lab 2.exe`.

لا يحتاج البرنامج إلى Setup؛ النسخ الجاهزة موزعة كحزم Portable.

---

## الخصوصية والأمان

Athar Fault Lab 2 هو برنامج محاكاة محلي ولا يقوم بـ:

- مهاجمة مواقع حقيقية
- تنفيذ DDoS
- حقن أعطال في خوادم خارجية
- استغلال الشبكات
- تعديل أنظمة إنتاجية
- إرسال Traffic ضار إلى بنية تحتية حقيقية

جميع الخدمات والطلبات والأعطال موجودة داخل نموذج المحاكاة المحلي.

---

## استخدامات مقترحة

- مشاريع الجامعة
- العروض الأكاديمية
- دراسة Reliability
- دراسة Fault Injection
- فهم أثر الأعطال المترابطة
- مقارنة أداء الخدمات
- تجربة سيناريوهات الضغط
- شرح البنية متعددة الطبقات للمواقع
- Portfolio لمطور C++/Qt
- التدريب على تصميم تطبيقات Desktop

---

## ملاحظات

- النتائج ناتجة عن محاكاة وليست قياسات لخادم حقيقي.
- بعض السيناريوهات تعتمد على الاحتمالات.
- قد تختلف النتائج قليلًا بين تشغيل وآخر.
- بيانات History تُخزن محليًا.
- لا يحتاج المحرك الأساسي إلى اتصال إنترنت.

---

## الإصدار

**Athar Fault Lab 2 v2.0**

يدعم:

- Windows x64
- Windows x86
- العربية
- English
- Dark Theme
- Light Theme

---

## المطور

**abdulaziz alyousef**

GitHub:  
https://github.com/abdulaziz-alyousef

Repository:  
https://github.com/abdulaziz-alyousef/Athar-Fault-Lab-2

---

# English

## Overview

**Athar Fault Lab 2** is a native Windows desktop simulation laboratory developed in **C++** with **Qt Widgets**.

The application models a simplified website infrastructure and allows users to study how failures affect request processing, service availability, latency, failure rates, and overall infrastructure health.

It does not attack, probe, or send fault traffic to real websites. All requests, services, failures, and metrics are simulated locally for educational and experimental purposes.

Athar Fault Lab 2 provides a complete desktop environment for configuring services, injecting faults, running simulations, observing infrastructure behavior, storing historical runs, and exporting reports.

---

## Project Concept

The simulated request path is:

```text
Client
  ↓
Gateway
  ↓
Web Server
  ↓
Application API
  ↓
Database
```

Each incoming simulated request travels through the infrastructure in sequence.

Every service has its own configuration, including:

- Worker count
- Failed workers
- Active workers
- Base latency
- Failure rate
- Availability
- Active fault state

During a simulation, faults can reduce service capacity, increase latency, reject requests, interrupt communication, or increase pressure.

---

## Project Goals

Athar Fault Lab 2 demonstrates and explores:

- Fault injection
- Website infrastructure behavior
- Service degradation
- Request flow
- Failure propagation
- Latency changes
- Worker capacity
- Traffic pressure
- Runtime metrics
- Infrastructure health
- Historical comparison
- Report generation

It is designed as both an educational project and a portfolio-level C++/Qt desktop application.

---

## Main Features

### Dashboard

The Dashboard provides a real-time summary of the simulation and infrastructure state.

It presents information such as:

- Infrastructure health
- Total requests
- Successful requests
- Failed requests
- Runtime latency
- Failure behavior
- Live performance changes
- Service status

Charts are custom-painted using Qt's QPainter system.

### Simulation

The Simulation page lets users configure:

- Total requests
- Arrival rate
- Simulation duration

Controls:

- Start
- Stop
- Reset

It also displays progress and current execution status.

### Services

The infrastructure contains:

| Service | Purpose |
|---|---|
| Gateway | Entry point for requests |
| Web Server | Web request processing layer |
| Application API | Application logic layer |
| Database | Data layer |

Configurable values include:

- Total Workers
- Failed Workers
- Active Workers
- Base Latency
- Failure Rate
- Available Workers

Default values:

| Service | Workers | Base Latency |
|---|---:|---:|
| Gateway | 12 | 4 ms |
| Web Server | 8 | 12 ms |
| Application API | 8 | 18 ms |
| Database | 8 | 25 ms |

---

## Supported Faults

### Worker Crash
Simulates workers becoming unavailable inside a service.

### Service Down
Simulates a complete service outage.

### Slowdown
Increases service processing latency.

### Error Spike
Temporarily increases request failure probability.

### Traffic Spike
Simulates a sudden increase in workload.

### DNS Failure
Simulates request failure at the entry stage.

### TLS Failure
Simulates secure connection establishment failure.

### Memory Pressure
Simulates degraded behavior caused by memory pressure.

### Storage Full
Simulates storage-related failure conditions.

### Retry Storm
Simulates repeated retries that increase system pressure.

### Link Outage
Simulates connectivity loss between infrastructure components.

---

## Network View

The Network View visualizes:

```text
Client → Gateway → Web Server → Application API → Database
```

States include:

- ONLINE
- DEGRADED
- OFFLINE

The view can also present worker count, latency, failure rate, active fault, and service state.

---

## History

Athar Fault Lab 2 uses a local **SQLite** database:

```text
data/athar_history.db
```

The History page allows users to:

- Review previous simulation runs
- Inspect stored results
- Select historical runs
- Use stored results in reports
- Clear history

Runtime database files are excluded from the Git repository.

---

## Reports

Reports can be generated from current or historical runs.

Supported formats:

- PNG
- JPG
- PDF

Report output follows the active application theme where applicable.

---

## Arabic and English Interface

The application supports:

- Arabic
- English

Arabic uses appropriate RTL behavior, while English uses LTR.

The internal language system updates interface elements including labels, buttons, tables, menus, actions, list items, and combo boxes.

---

## Dark and Light Themes

Athar Fault Lab 2 supports:

- Dark Theme
- Light Theme

The selected appearance is stored using QSettings and restored on future launches.

---

## Splash Screen

The application opens with a dedicated splash screen and transitions into the main window using a fade animation.

---

## Simulation Flow

```text
Request Created
      ↓
Gateway
      ↓
Web Server
      ↓
Application API
      ↓
Database
      ↓
Result
```

At each stage, the simulation considers:

- Available workers
- Base latency
- Failure probability
- Active fault
- Service state
- Runtime pressure

A request that fails may stop before reaching later services. A request that completes the full path is counted as successful.

---

## Configured Failure vs Runtime Failure

Configured failure probability is not necessarily identical to the observed runtime failure percentage.

Configured values represent the probabilities used by the simulation, while runtime metrics represent the actual results produced during a specific run.

Because some behaviors are probabilistic, identical configuration can produce slightly different results.

---

## Technical Stack

- **C++17**
- **Qt Widgets**
- **CMake**
- **SQLite**
- **Qt SQL**
- **QSettings**
- **QPainter**
- **Windows Resource Files**
- **Windows DWM API**

On Windows, the application links against:

```text
dwmapi
```

---

## Project Structure

```text
Athar-Fault-Lab-2/
│
├── CMakeLists.txt
├── .gitignore
│
├── resources/
│   ├── athar.ico
│   └── athar.rc
│
└── src/
    ├── main.cpp
    ├── simulation/
    │   ├── Fault.cpp
    │   ├── Fault.h
    │   ├── Service.cpp
    │   ├── Service.h
    │   ├── SimulationEngine.cpp
    │   └── SimulationEngine.h
    ├── storage/
    │   ├── HistoryManager.cpp
    │   └── HistoryManager.h
    └── ui/
        ├── MainWindow.cpp
        ├── MainWindow.h
        ├── SplashScreen.cpp
        ├── SplashScreen.h
        ├── Dashboard.cpp
        ├── Dashboard.h
        ├── FaultPanel.cpp
        ├── FaultPanel.h
        ├── MetricsPanel.cpp
        ├── MetricsPanel.h
        ├── NetworkView.cpp
        ├── NetworkView.h
        ├── HistoryPanel.cpp
        ├── HistoryPanel.h
        ├── ReportsPanel.cpp
        ├── ReportsPanel.h
        └── UiLanguage.h
```

---

## Main Components

### `main.cpp`
Application entry point, metadata, theme loading, splash startup, and main window creation.

### `SimulationEngine`
Main simulation logic and runtime request processing.

### `Service`
Represents an infrastructure service and its configuration.

### `Fault`
Represents fault types and fault-related behavior.

### `HistoryManager`
Handles SQLite storage for simulation history.

### `MainWindow`
Main application window and UI coordinator.

### `Dashboard`
Displays infrastructure health and runtime summary.

### `FaultPanel`
Provides fault injection controls.

### `MetricsPanel`
Displays simulation metrics.

### `NetworkView`
Visualizes infrastructure and service states.

### `HistoryPanel`
Displays stored simulation history.

### `ReportsPanel`
Provides report viewing and export functionality.

### `UiLanguage.h`
Provides the internal Arabic/English translation system.

---

## Building from Source

### Requirements

- Windows
- CMake 3.21 or newer
- A C++17-compatible compiler
- Qt Widgets
- Qt SQL

Tested environments:

### x64
```text
Qt 6.11.2
MSVC 2022 64-bit
```

### x86
```text
Qt 5.15.2
MinGW 32-bit
```

### Build with Qt Creator

1. Open `CMakeLists.txt`.
2. Select the appropriate Qt Kit.
3. Select Release.
4. Configure the project.
5. Build the target.
6. The executable is produced as:

```text
Athar Fault Lab 2.exe
```

---

## Prebuilt Downloads

Prebuilt packages are available from the GitHub **Releases** page.

### Windows x64

```text
Athar-Fault-Lab-2-v2.0-Windows-x64.zip
```

Recommended for modern 64-bit Windows systems.

### Windows x86

```text
Athar-Fault-Lab-2-v2.0-Windows-x86.zip
```

Designed for 32-bit Windows environments.

After downloading:

1. Extract the ZIP file.
2. Open the extracted folder.
3. Run `Athar Fault Lab 2.exe`.

No installer is required. Releases are distributed as portable Windows packages.

---

## Safety and Scope

Athar Fault Lab 2 is a local simulation tool.

It does **not**:

- Attack real websites
- Perform DDoS
- Inject faults into external servers
- Exploit networks
- Modify production systems
- Send destructive traffic to real infrastructure

All services, requests, and faults exist inside the local simulation model.

---

## Suggested Uses

- University projects
- Academic demonstrations
- Reliability concepts
- Fault injection demonstrations
- Infrastructure behavior analysis
- Service degradation experiments
- Traffic pressure experiments
- Multi-layer request flow explanation
- C++/Qt portfolio work
- Desktop software architecture practice

---

## Notes

- Results are simulation results, not measurements from production servers.
- Some scenarios use probabilistic behavior.
- Identical settings may produce slightly different runtime results.
- History data is stored locally.
- Internet access is not required for the core simulation.

---

## Version

**Athar Fault Lab 2 v2.0**

Supports:

- Windows x64
- Windows x86
- Arabic
- English
- Dark Theme
- Light Theme

---

## Developer

**abdulaziz alyousef**

GitHub:  
https://github.com/abdulaziz-alyousef

Repository:  
https://github.com/abdulaziz-alyousef/Athar-Fault-Lab-2

---

## License

No license has been specified for this repository at this time.

Unless a license is added later, source code reuse, redistribution, and modification rights are not automatically granted.

---

<div align="center">

**Athar Fault Lab 2**

Website Fault Simulation Laboratory

Made by **abdulaziz alyousef**

</div>
