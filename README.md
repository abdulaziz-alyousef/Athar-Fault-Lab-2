# Athar Fault Lab 2 | أثر العطل 2

<div align="center">

**Website Fault Simulation Laboratory**  
**مختبر محاكاة أعطال المواقع**

A desktop simulation environment for studying how website services behave under failures, pressure, slowdowns, and abnormal operating conditions.

بيئة محاكاة مكتبية لدراسة سلوك خدمات المواقع عند حدوث الأعطال والضغط والبطء والحالات غير الطبيعية.

**Made by: abdulaziz alyousef**

</div>

---

# العربية

## نظرة عامة

**Athar Fault Lab 2 | أثر العطل 2** هو برنامج محاكاة تعليمي وتجريبي يهدف إلى توضيح ما يحدث داخل البنية التحتية للمواقع الإلكترونية عند تعرض إحدى خدماتها لعطل أو ضغط أو بطء أو ارتفاع في نسبة الأخطاء.

يقوم البرنامج بتمثيل مجموعة من الخدمات التي تعمل معًا لمعالجة طلبات المستخدمين، ثم يسمح للمستخدم بتشغيل محاكاة لهذه الطلبات ومراقبة طريقة انتقالها بين الخدمات، ومدى تأثر النظام عند حدوث مشكلة في جزء معين من البنية التحتية.

البرنامج يعمل كمختبر افتراضي محلي بالكامل، ولا يقوم بإرسال أعطال أو هجمات أو طلبات ضارة إلى مواقع حقيقية. جميع الخدمات والأعطال والطلبات التي تظهر داخل البرنامج هي جزء من نموذج محاكاة داخلي تم إنشاؤه لأغراض التعلم، التجربة، التحليل، والعرض الأكاديمي.

---

## فكرة البرنامج

تعتمد فكرة البرنامج على محاكاة مسار طلب المستخدم داخل موقع إلكتروني.

المسار الأساسي للطلب هو:

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

يمثل كل جزء مرحلة مختلفة من مراحل معالجة الطلب.

عند بدء المحاكاة يتم إنشاء طلبات افتراضية تمر من خلال هذه الخدمات بالتسلسل. أثناء مرور الطلب يتم احتساب تأثير حالة كل خدمة، وعدد العمال المتاحين، وزمن الاستجابة، ونسبة الفشل، والأعطال النشطة.

إذا كانت جميع الخدمات تعمل بصورة طبيعية، يمكن للطلب إكمال مساره بنجاح.

أما إذا كانت إحدى الخدمات متوقفة أو بطيئة أو تعاني من ضغط أو أخطاء، فقد يتأخر الطلب أو يفشل قبل أن يصل إلى نهاية المسار.

بهذا الأسلوب يستطيع المستخدم رؤية أثر المشكلة بصورة واضحة بدلًا من الاكتفاء بقراءة أرقام منفصلة.

---

## الهدف من Athar Fault Lab 2

تم تصميم البرنامج لتوضيح مجموعة من المفاهيم المهمة المتعلقة بموثوقية الأنظمة والخدمات، مثل:

- تأثير الأعطال على تجربة المستخدم.
- تأثير توقف خدمة واحدة على بقية النظام.
- العلاقة بين عدد العمال المتاحين وقدرة الخدمة على معالجة الطلبات.
- أثر ارتفاع زمن الاستجابة على الأداء العام.
- أثر ارتفاع نسبة الفشل.
- تأثير زيادة حركة الطلبات بشكل مفاجئ.
- تأثير الضغط المتكرر وإعادة المحاولة.
- الفرق بين الحالة الطبيعية والحالة المتدهورة والحالة المتوقفة.
- كيفية انتقال أثر العطل من خدمة إلى أخرى.
- كيفية قراءة مؤشرات الأداء أثناء حدوث المشكلة.

---

# صفحات البرنامج

## Dashboard | لوحة المعلومات

لوحة المعلومات هي الصفحة الرئيسية لمتابعة حالة المحاكاة بصورة سريعة.

تعرض الصفحة مجموعة من المؤشرات التي تساعد على فهم حالة النظام أثناء التشغيل، مثل:

- إجمالي عدد الطلبات.
- عدد الطلبات الناجحة.
- عدد الطلبات الفاشلة.
- معدل الفشل.
- زمن الاستجابة.
- حالة البنية التحتية.
- حالة الخدمات.
- التغير في الأداء أثناء المحاكاة.

كما تحتوي على رسوم ومؤشرات مرئية تساعد على ملاحظة التغيرات أثناء حدوث الأعطال.

الهدف من لوحة المعلومات هو إعطاء المستخدم نظرة شاملة على النظام دون الحاجة إلى متابعة كل خدمة بشكل منفصل.

---

## Simulation | المحاكاة

صفحة المحاكاة هي المكان الذي يتم من خلاله التحكم في تشغيل التجربة.

يمكن للمستخدم تحديد إعدادات مثل:

- إجمالي عدد الطلبات.
- معدل وصول الطلبات.
- مدة المحاكاة.

ثم يمكنه التحكم بالمحاكاة من خلال:

- Start
- Stop
- Reset

أثناء التشغيل يتم عرض حالة المحاكاة والتقدم الذي وصلت إليه.

هذه الصفحة تمثل نقطة البداية لأي تجربة داخل البرنامج، حيث يتم تحديد الحمل الأساسي ثم مراقبة النتائج على بقية الصفحات.

---

## Services | الخدمات

يحتوي البرنامج على أربع خدمات رئيسية تمثل بنية موقع إلكتروني مبسطة:

### Gateway

تمثل نقطة دخول الطلبات إلى النظام.

وهي أول خدمة يتعامل معها الطلب قبل الانتقال إلى بقية أجزاء البنية التحتية.

### Web Server

تمثل طبقة خادم الويب التي تستقبل الطلب بعد مروره من البوابة.

### Application API

تمثل طبقة منطق التطبيق ومعالجة العمليات الداخلية.

### Database

تمثل طبقة البيانات التي تنتهي عندها بعض العمليات وتتم فيها معالجة البيانات المطلوبة.

---

## إعدادات الخدمات

لكل خدمة مجموعة من القيم التي يمكن تعديلها لمراقبة أثرها على النظام.

من أهمها:

### Total Workers

يمثل إجمالي عدد العمال أو الوحدات القادرة على معالجة الطلبات داخل الخدمة.

كلما زاد عدد العمال، زادت القدرة النظرية للخدمة على التعامل مع عدد أكبر من الطلبات.

### Failed Workers

يمثل عدد العمال غير القادرين على العمل بسبب عطل أو مشكلة.

### Active Workers

يمثل العمال الذين ما زالوا يعملون بصورة فعلية.

### Base Latency

يمثل زمن الاستجابة الأساسي للخدمة قبل إضافة تأثير الأعطال والضغط.

### Failure Rate

يمثل احتمال فشل الطلب داخل الخدمة.

### Available Workers

يمثل عدد العمال المتاحين فعليًا لاستقبال ومعالجة الطلبات.

---

# Fault Injection | حقن الأعطال

من أهم أجزاء Athar Fault Lab 2 نظام حقن الأعطال.

يسمح البرنامج للمستخدم بتطبيق سيناريوهات مختلفة على الخدمات لمعرفة كيف تتغير حالة النظام عند حدوث مشكلة.

---

## Worker Crash

يحاكي تعطل جزء من العمال داخل خدمة معينة.

عند حدوث هذا العطل تقل القدرة المتاحة للخدمة على معالجة الطلبات، وقد يؤدي ذلك إلى زيادة الضغط أو التأخير أو ارتفاع الفشل عند استمرار وصول الطلبات.

---

## Service Down

يحاكي توقف خدمة بالكامل.

عندما تتوقف خدمة أساسية داخل المسار، تصبح غير قادرة على معالجة الطلبات التي تصل إليها، ويمكن أن يؤدي ذلك إلى فشل عدد كبير من الطلبات.

---

## Slowdown

يحاكي حدوث بطء داخل خدمة معينة.

في هذا السيناريو تستمر الخدمة بالعمل، لكنها تحتاج إلى وقت أطول لمعالجة الطلبات.

هذا يسمح للمستخدم بملاحظة الفرق بين توقف الخدمة بالكامل وبين استمرارها مع تدهور الأداء.

---

## Error Spike

يحاكي ارتفاعًا مفاجئًا في نسبة الأخطاء.

قد تكون الخدمة ظاهريًا متاحة، لكن نسبة أكبر من الطلبات قد تفشل أثناء مرورها من خلالها.

---

## Traffic Spike

يحاكي زيادة مفاجئة في حجم حركة الطلبات.

الهدف منه هو دراسة كيفية تغير أداء النظام عندما يصل إليه عدد أكبر من الطلبات خلال فترة قصيرة.

---

## DNS Failure

يحاكي فشلًا في مرحلة وصول المستخدم إلى النظام.

في هذا السيناريو قد تفشل بعض الطلبات قبل أن تبدأ رحلتها داخل الخدمات الأساسية.

---

## TLS Failure

يحاكي فشلًا في مرحلة إنشاء الاتصال الآمن قبل بدء المعالجة الطبيعية للطلب.

يمكن استخدامه لدراسة أثر مشاكل الاتصال الأولية على إجمالي نسبة نجاح الطلبات.

---

## Memory Pressure

يحاكي ضغطًا على الذاكرة وتأثيره على أداء الخدمة.

يمكن أن يؤدي هذا النوع من الضغط إلى تدهور في الاستجابة أو انخفاض في القدرة على التعامل مع الطلبات.

---

## Storage Full

يحاكي حالة امتلاء التخزين وتأثيرها على العمليات التي تحتاج إلى كتابة أو حفظ بيانات.

---

## Retry Storm

يحاكي حالة تقوم فيها الطلبات الفاشلة بإعادة المحاولة بصورة متكررة.

بدلًا من تخفيف المشكلة، يمكن أن تؤدي إعادة المحاولة المستمرة إلى زيادة الضغط على النظام ورفع الحمل على الخدمات.

---

## Link Outage

يحاكي انقطاع الاتصال بين أجزاء من البنية التحتية.

في هذه الحالة قد تكون الخدمات نفسها تعمل، لكن الطلب لا يستطيع الانتقال بينها بصورة طبيعية.

---

# Network View | عرض الشبكة

تقدم صفحة Network View تمثيلًا بصريًا لمسار الطلب داخل النظام:

```text
Client → Gateway → Web Server → Application API → Database
```

تساعد هذه الصفحة على معرفة مكان المشكلة بسرعة.

تعرض الخدمات بحالات مختلفة مثل:

- **ONLINE** — الخدمة تعمل بصورة طبيعية.
- **DEGRADED** — الخدمة تعمل ولكن بأداء متدهور.
- **OFFLINE** — الخدمة متوقفة أو غير قادرة على العمل.

كما تعرض معلومات مرتبطة بالخدمات مثل:

- العمال.
- زمن الاستجابة.
- نسبة الفشل.
- حالة الخدمة.
- العطل النشط.

هذه الصفحة مفيدة خصوصًا عند تشغيل أعطال متعددة ورؤية تأثيرها على المسار الكامل.

---

# History | سجل المحاكاة

يحفظ البرنامج نتائج عمليات المحاكاة السابقة محليًا.

تتيح صفحة History للمستخدم الرجوع إلى التجارب السابقة ومراجعة نتائجها بدلًا من فقدانها بعد انتهاء التشغيل.

يمكن من خلالها:

- مشاهدة عمليات المحاكاة السابقة.
- مراجعة وقت وتاريخ التشغيل.
- مراجعة النتائج.
- اختيار تجربة سابقة.
- استخدام نتائج سابقة في التقارير.
- مسح السجل عند الحاجة.

هذه الميزة مفيدة عند إجراء أكثر من تجربة ومقارنة النتائج بينها.

---

# Reports | التقارير

يحتوي البرنامج على قسم خاص بالتقارير.

يسمح للمستخدم بإنشاء تقرير اعتمادًا على:

- المحاكاة الحالية.
- أو تشغيل سابق محفوظ في History.

يمكن تصدير التقارير بعدة صيغ، منها:

- PNG
- JPG
- PDF

تساعد هذه الميزة على حفظ النتائج ومشاركتها واستخدامها في العروض الأكاديمية أو التوثيق.

---

# العربية والإنجليزية

يدعم البرنامج واجهتين:

- العربية
- English

يمكن للمستخدم التبديل بين اللغتين من داخل التطبيق.

عند اختيار العربية يتم استخدام الاتجاه المناسب للنصوص العربية، بينما تستخدم الإنجليزية الاتجاه المعتاد من اليسار إلى اليمين.

الهدف هو جعل البرنامج مناسبًا للمستخدم العربي وفي الوقت نفسه سهل الاستخدام باللغة الإنجليزية.

---

# الوضع الداكن والفاتح

يدعم Athar Fault Lab 2 مظهرين:

- Dark Theme
- Light Theme

يمكن للمستخدم اختيار المظهر المناسب له.

يتم تطبيق المظهر على مختلف أجزاء الواجهة مثل:

- الصفحات.
- الجداول.
- الأزرار.
- القوائم.
- النوافذ.
- شاشة البداية.
- التقارير.

ويحتفظ البرنامج باختيار المستخدم لاستخدامه عند التشغيل التالي.

---

# Splash Screen | شاشة البداية

عند تشغيل Athar Fault Lab 2 تظهر شاشة بداية تحمل هوية البرنامج قبل فتح الواجهة الرئيسية.

تم تصميم شاشة البداية لتكون جزءًا من تجربة الاستخدام وتعكس المظهر المختار للبرنامج.

---

# كيف تعمل المحاكاة؟

يمكن تلخيص طريقة عمل البرنامج في الخطوات التالية:

1. يقوم المستخدم باختيار إعدادات المحاكاة.
2. يبدأ البرنامج في إنشاء طلبات افتراضية.
3. يدخل الطلب من خلال Gateway.
4. ينتقل إلى Web Server.
5. ثم ينتقل إلى Application API.
6. ثم يصل إلى Database.
7. يتم احتساب أثر كل خدمة على الطلب.
8. إذا حدث عطل أو فشل في إحدى المراحل، قد يتوقف الطلب.
9. إذا نجح الطلب في المرور عبر المسار المطلوب، يتم احتسابه كطلب ناجح.
10. يتم تحديث المؤشرات والرسوم والنتائج أثناء التشغيل.

---

# ما الذي يؤثر على نتيجة الطلب؟

تعتمد نتيجة الطلب على مجموعة من العوامل، منها:

- حالة الخدمة.
- عدد العمال المتاحين.
- زمن الاستجابة.
- نسبة الفشل.
- العطل النشط.
- الضغط الحالي.
- عدد الطلبات الداخلة إلى النظام.
- وجود انقطاع أو مشكلة في مرحلة من مراحل المسار.

لذلك فإن تغيير قيمة واحدة فقط يمكن أن يؤدي إلى تغير واضح في النتيجة النهائية.

---

# الفرق بين الإعداد والنتيجة الفعلية

بعض القيم داخل البرنامج تمثل إعدادات احتمالية.

على سبيل المثال، عندما يتم تحديد نسبة فشل معينة فهذا لا يعني بالضرورة أن النتيجة النهائية ستكون مطابقة لها حرفيًا.

النسبة المحددة تمثل احتمالًا تستخدمه المحاكاة، بينما Runtime Failure يمثل النتيجة الفعلية التي حدثت خلال تشغيل معين.

ولهذا يمكن أن تظهر فروقات بسيطة بين تجربة وأخرى حتى عند استخدام إعدادات متشابهة.

---

# أمثلة على التجارب الممكنة

يمكن استخدام البرنامج لإجراء تجارب مثل:

### تجربة النظام الطبيعي

تشغيل المحاكاة دون أي أعطال لمشاهدة الأداء الأساسي للنظام.

### تجربة توقف قاعدة البيانات

إيقاف Database ومراقبة تأثير ذلك على الطلبات.

### تجربة بطء Application API

زيادة زمن الاستجابة في طبقة التطبيق وملاحظة ارتفاع زمن الاستجابة العام.

### تجربة ضغط مفاجئ

تطبيق Traffic Spike ومراقبة تأثير زيادة الطلبات على الخدمات.

### تجربة تعطل العمال

تقليل عدد العمال النشطين في خدمة ومراقبة مدى قدرتها على الاستمرار.

### تجربة Retry Storm

تطبيق إعادة المحاولة المتكررة وملاحظة كيف يمكن أن يؤدي الضغط الإضافي إلى زيادة المشكلة.

### تجربة أكثر من عطل

يمكن إنشاء سيناريوهات أكثر تعقيدًا عبر الجمع بين أكثر من حالة ومراقبة تأثيرها على النظام.

---

# الاستخدام التعليمي

تم تصميم Athar Fault Lab 2 ليكون مناسبًا للاستخدام في:

- المشاريع الجامعية.
- العروض الأكاديمية.
- دراسة أساسيات موثوقية الأنظمة.
- شرح مفهوم Fault Injection.
- دراسة الأعطال المتسلسلة.
- دراسة تأثير الضغط.
- فهم البنية متعددة الخدمات.
- شرح العلاقة بين الأداء والتوفر والفشل.
- تدريب المستخدم على قراءة مؤشرات النظام.

---

# الأمان ونطاق البرنامج

Athar Fault Lab 2 هو برنامج محاكاة محلي فقط.

لا يقوم البرنامج بـ:

- مهاجمة مواقع حقيقية.
- إرسال DDoS.
- تنفيذ اختبارات اختراق على خوادم حقيقية.
- تعطيل مواقع خارجية.
- تعديل أنظمة حقيقية.
- إرسال Fault Injection إلى شبكة خارجية.
- تنفيذ عمليات ضارة على الإنترنت.

جميع الأعطال والخدمات والطلبات الموجودة داخل البرنامج افتراضية ومحلية.

الغرض من البرنامج هو التعلم والمحاكاة والتحليل فقط.

---

# لمن تم تصميم البرنامج؟

يمكن أن يكون Athar Fault Lab 2 مفيدًا لـ:

- طلاب الحاسب.
- طلاب هندسة البرمجيات.
- المهتمين بمحاكاة الأنظمة.
- المهتمين بموثوقية الخدمات.
- المهتمين بفهم البنية التحتية للمواقع.
- من يريد تجربة سيناريوهات الأعطال داخل بيئة آمنة.
- من يريد مشروعًا تفاعليًا لعرض مفاهيم Fault Injection.

---

# ملاحظات مهمة

- النتائج التي يعرضها البرنامج هي نتائج محاكاة وليست قياسات لموقع حقيقي.
- بعض النتائج تعتمد على الاحتمالات، لذلك قد تختلف قليلًا بين تشغيل وآخر.
- البرنامج يعمل محليًا ولا يحتاج إلى الاتصال بموقع حقيقي لإجراء التجارب.
- يمكن استخدام History لمقارنة أكثر من تشغيل.
- يمكن استخدام Reports لحفظ نتائج التجارب.
- يمكن تغيير إعدادات الخدمات قبل تشغيل المحاكاة.
- يمكن تطبيق الأعطال ومراقبة تأثيرها بصريًا أثناء التجربة.

---

# الإصدار

**Athar Fault Lab 2 v2.0**

يدعم:

- Windows x64
- Windows x86
- Dark Theme
- Light Theme

---

# المطور

**abdulaziz alyousef**

GitHub:  
https://github.com/abdulaziz-alyousef

Repository:  
https://github.com/abdulaziz-alyousef/Athar-Fault-Lab-2

---

# English

## Overview

**Athar Fault Lab 2** is an educational and experimental desktop simulation application designed to demonstrate how website infrastructure behaves when services experience failures, overload, slow response, reduced capacity, or other abnormal operating conditions.

The application represents a simplified website environment made of multiple services working together to process user requests.

Users can run simulated workloads, change service behavior, inject faults, observe live results, review previous runs, and export reports.

Athar Fault Lab 2 operates as a local simulation laboratory. It does not send attacks, destructive traffic, or injected faults to real websites.

All services, requests, and failures exist entirely inside the simulation environment.

---

## Program Concept

The application models a simplified request path:

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

Each request travels through the infrastructure in sequence.

At every stage, the request can be affected by:

- Service availability.
- Available workers.
- Base latency.
- Failure probability.
- Active faults.
- Current system pressure.

When all services operate normally, requests have a greater chance of completing successfully.

When a service becomes slow, unavailable, overloaded, or unstable, the effect can propagate through the rest of the simulated infrastructure.

---

## Main Purpose

Athar Fault Lab 2 is designed to help users understand:

- How service failures affect request processing.
- How a single degraded service can affect an entire system.
- How latency changes affect user-facing performance.
- How worker capacity affects service throughput.
- How sudden traffic increases affect system behavior.
- How retry behavior can create additional pressure.
- How faults can propagate across multiple service layers.
- How to interpret runtime metrics during abnormal conditions.

---

# Application Pages

## Dashboard

The Dashboard provides a quick overview of the current simulation and infrastructure state.

It can display information such as:

- Total requests.
- Successful requests.
- Failed requests.
- Failure rate.
- Response time.
- Infrastructure health.
- Service state.
- Live performance changes.

Visual indicators and charts make it easier to observe how the system changes during a simulation.

---

## Simulation

The Simulation page controls the main experiment.

Users can configure values such as:

- Total requests.
- Request arrival rate.
- Simulation duration.

Main controls include:

- Start.
- Stop.
- Reset.

The page also displays simulation progress and execution status.

---

## Services

The application represents four primary infrastructure services.

### Gateway

The request entry point.

### Web Server

The web processing layer.

### Application API

The application logic layer.

### Database

The data-processing layer.

---

## Service Settings

Each service can be configured using values such as:

### Total Workers

The total processing capacity available to the service.

### Failed Workers

Workers that are currently unavailable.

### Active Workers

Workers that are still functioning.

### Base Latency

The normal response delay before additional fault or pressure effects.

### Failure Rate

The probability that a request fails inside the service.

### Available Workers

The workers currently available to process requests.

---

# Fault Injection

One of the central features of Athar Fault Lab 2 is fault injection.

Users can introduce different failure scenarios and observe their effect on the complete system.

---

## Worker Crash

Simulates workers becoming unavailable inside a service.

This reduces processing capacity and can increase pressure on the remaining workers.

---

## Service Down

Simulates a complete service outage.

Requests reaching the unavailable service may fail and become unable to continue through the request path.

---

## Slowdown

Simulates degraded performance by increasing service processing time.

The service remains operational but responds more slowly.

---

## Error Spike

Simulates a sudden increase in request errors.

The service may remain available while producing a larger number of failed requests.

---

## Traffic Spike

Simulates a sudden increase in incoming workload.

This scenario helps demonstrate how increased demand affects infrastructure performance.

---

## DNS Failure

Simulates failure during the initial stage of reaching the system.

Some requests may fail before entering the internal service path.

---

## TLS Failure

Simulates secure connection establishment failure before normal request processing begins.

---

## Memory Pressure

Simulates degraded service behavior caused by memory pressure.

---

## Storage Full

Simulates conditions where storage-dependent operations are affected by unavailable storage capacity.

---

## Retry Storm

Simulates repeated retry behavior after failures.

Repeated retries can increase pressure on an already degraded system and make recovery more difficult.

---

## Link Outage

Simulates a connectivity failure between infrastructure components.

A service may still be running, but requests may be unable to reach it.

---

# Network View

The Network View presents the simulated infrastructure visually:

```text
Client → Gateway → Web Server → Application API → Database
```

Services can appear in states such as:

- **ONLINE**
- **DEGRADED**
- **OFFLINE**

The view helps users identify where a problem is happening and how that problem affects the rest of the request path.

It can also show information such as:

- Worker state.
- Latency.
- Failure rate.
- Active fault.
- Service condition.

---

# History

Athar Fault Lab 2 stores previous simulation results locally.

The History page allows users to:

- Review previous simulation runs.
- View recorded results.
- Compare different experiments.
- Select a previous run.
- Use a saved run for report generation.
- Clear stored history when needed.

This is useful when performing multiple experiments with different settings.

---

# Reports

The Reports section allows users to create reports from simulation results.

Reports can be generated from:

- The current simulation.
- A previously saved run.

Supported export formats include:

- PNG.
- JPG.
- PDF.

Reports are useful for documentation, presentations, academic work, and comparison between experiments.

---

# Arabic and English

Athar Fault Lab 2 supports two interface languages:

- Arabic.
- English.

Users can switch between them inside the application.

Arabic uses appropriate right-to-left behavior, while English uses left-to-right layout behavior.

---

# Dark and Light Themes

The application includes:

- Dark Theme.
- Light Theme.

The selected appearance is applied across the interface, including pages, controls, tables, dialogs, the splash screen, and reports.

The application remembers the user's selected appearance for future launches.

---

# Splash Screen

Athar Fault Lab 2 includes a dedicated startup screen that appears before the main application window.

The splash screen follows the selected application appearance.

---

# How the Simulation Works

A typical request follows this path:

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

During processing, the simulation evaluates the condition of each service.

A request may be affected by:

- Worker availability.
- Latency.
- Failure probability.
- Active fault.
- Service state.
- Current workload.

If the request fails at one stage, it may stop before reaching later services.

If the request completes the required path successfully, it is counted as successful.

---

# What Affects a Request?

Request results can be influenced by:

- Service state.
- Number of available workers.
- Base response time.
- Failure probability.
- Active fault type.
- Current pressure.
- Incoming workload.
- Connectivity between services.

Because multiple factors can interact, changing one service can affect the behavior of the full infrastructure.

---

# Configured Failure vs Runtime Failure

A configured failure rate represents the probability used by the simulation.

It does not mean the final observed runtime failure percentage must be exactly identical.

Runtime results represent what actually happened during a particular simulation run.

Because some behavior is probabilistic, repeated runs with similar settings may produce slightly different results.

---

# Example Experiments

## Normal Operation

Run the simulation without faults to observe baseline behavior.

## Database Outage

Take the Database service down and observe the impact on request success.

## API Slowdown

Increase the response delay of the Application API and monitor overall latency.

## Traffic Spike

Increase incoming request pressure and observe service behavior.

## Worker Failure

Reduce active workers and observe how service capacity changes.

## Retry Storm

Introduce repeated retry behavior and observe how pressure increases.

## Combined Faults

Use multiple faults together to create more complex scenarios.

---

# Educational Use

Athar Fault Lab 2 is suitable for:

- University projects.
- Academic demonstrations.
- Reliability concepts.
- Fault injection demonstrations.
- Failure propagation experiments.
- Traffic pressure experiments.
- Multi-service architecture demonstrations.
- Understanding the relationship between performance, availability, and failure.
- Learning how to interpret runtime system metrics.

---

# Safety and Scope

Athar Fault Lab 2 is a local simulation application.

It does **not**:

- Attack real websites.
- Perform DDoS.
- Inject faults into external servers.
- Exploit networks.
- Disable real infrastructure.
- Modify production systems.
- Send destructive traffic over the Internet.

All faults and services are simulated locally.

The application is intended for education, experimentation, analysis, and demonstration.

---

# Intended Users

Athar Fault Lab 2 can be useful for:

- Computer science students.
- Software engineering students.
- Users interested in system simulation.
- Users interested in service reliability.
- Users learning website infrastructure concepts.
- Users studying fault injection.
- Users looking for a safe environment for failure experiments.

---

# Important Notes

- Results represent simulation behavior, not measurements from real production websites.
- Some scenarios use probabilistic behavior.
- Results may vary slightly between simulation runs.
- History is stored locally.
- Reports can be used to document experiments.
- Service settings can be changed before running simulations.
- Fault effects can be monitored visually during execution.

---

# Version

**Athar Fault Lab 2 v2.0**

Supports:

- Windows x64
- Windows x86
- Dark Theme
- Light Theme

---

# Developer

**abdulaziz alyousef**

GitHub:  
https://github.com/abdulaziz-alyousef

Repository:  
https://github.com/abdulaziz-alyousef/Athar-Fault-Lab-2

---

<div align="center">

**Athar Fault Lab 2**

Website Fault Simulation Laboratory

Made by **abdulaziz alyousef**

</div>
