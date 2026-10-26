## Brought to you by:
[![Quantum Leaps](https://www.state-machine.com/attachments/logo_ql_400.png)](https://www.state-machine.com)
<hr>

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/QuantumLeaps/Super-Simple-Tasker)](https://github.com/QuantumLeaps/Super-Simple-Tasker/releases/latest)
[![GitHub](https://img.shields.io/github/license/QuantumLeaps/Super-Simple-Tasker)](https://github.com/QuantumLeaps/Super-Simple-Tasker/blob/master/LICENSE)

# Super-Simple Tasker (SST)
Super-Simple Tasker (SST) is an event-driven, preemptive, priority-based
real-time operating system (RTOS) kernel that is fully compatible with
the requirements of
[Rate Monotonic Analysis/Scheduling (RMA/RMS)](https://youtu.be/kLxxXNCrY60).

<p align="center">
<a href="https://youtu.be/PTcauYl994A" target="_blank" title="SST video">
<img src="img/logo_sst_c-cpp.png"/></p>
</a></p>

The tasks in SST are non-blocking and run-to-completion, which are also known
as **basic tasks** in the
[OSEK/VDX Operating System Specification](https://www.irisa.fr/alf/downloads/puaut/TPNXT/images/os223.pdf). SST corresponds to the BCC2 conformance class in OSEK/VDX.
SST provides the following features:
- basic tasks (non-blocking, run-to-completion)
- preemptive, priority-based scheduling
- multiple tasks per priority level
- multiple "activations" per task (event queues)
- selective scheduler locking according to "Stack Resource Policy" (SRP)<br>
  (a non-blocking mutual exclusion mechanism for protecting shared resources)

> **NOTE**<br>
The execution profile of SST tasks perfectly matches the non-blocking and
run-to-completion semantics of event-driven state machines
(a.k.a. ["Active Objects" or "Actors](https://www.state-machine.com/active-object)).

This repository contains the SST following implementations:
- [preemptive SST in C](sst_c)
- [preemptive SST in C++](sst_cpp)

Additionally, this repository contains the even simpler, *non-preemptive*
implementation of basic tasks called [SST0](#non-preemptive-sst0):
- [non-preemptive SST0 in C](sst0_c)
- [non-preemptive SST0 in C++](sst0_cpp)


> **NOTE**<br>
The preemptive SST and non-preemptive SST0 implement actually *the same*
[SST API](https://github.com/QuantumLeaps/Super-Simple-Tasker/tree/main/include)
(either in C or C++).


## Related Approaches
The SST RTOS kernel is related to, although *not* based on, the following
approaches:

- [Operating System - OSEK VDX](https://www.osek-vdx.org/mirror/os21r1.pdf)
- [A Stack-Based Resource Allocation Policy for Realtime Processes](https://ieeexplore.ieee.org/document/128747)
- [Real-Time For the Masses](https://www.diva-portal.org/smash/get/diva2:1005680/FULLTEXT01.pdf)
- [crect: A C++, compile-time, reactive RTOS](https://github.com/korken89/crect)
- [Rust's Real Time For the Masses (RTFM)](https://lonesometraveler.github.io/2020/05/22/RTFM.html)
- [Real-Time Interrupt-driven Concurrency (RTIC)](https://rtic.rs/1/book/en)


# Hardware RTOS for ARM Cortex-M
[SST for ARM Cortex-M](sst_c/ports/arm-cm) provides a unique
**hardware implementation** of the SST API for ARM Cortex-M (M0, M0+, M3,
M4, M7, M23, M33). The SST "hardware RTOS" for ARM Cortex-M is fully
compatible with the requirements of
[Rate Monotonic Analysis/Scheduling (RMA/RMS)](https://youtu.be/kLxxXNCrY60).

<p align="center"><img src="img/logo_sst-arm-cm.png"/></p>

> **NOTE**<br>
The SST hardware implementation is likely the most performant and efficient
**hard-real time RTOS** kernel for ARM Cortex-M.


# Hardware RTOS for Microchip dsPIC
The contributed [SST port for dsPIC](sst_c/ports/dspic) provides a unique
**hardware implementation** of the SST API for
[Microchip dsPIC](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/dspic-dscs).
The SST "hardware RTOS" for dsPIC is fully compatible with the requirements of
[Rate Monotonic Analysis/Scheduling (RMA/RMS)](https://youtu.be/kLxxXNCrY60).

<p align="center"><img src="img/dsPIC.png"/></p>


# SST Videos
SST has been presented at the Embedded Online Conference 2023 and the videos
are available on YouTube:

<p align="center">
<a href="https://youtu.be/PTcauYl994A" target="_blank" title="SST video">
<img src="img/sst-video.jpg"/>
</a></p>


# SST History
SST has been originally published as a cover-story article
["Build a Super-Simple Tasker"](legacy/Super-Simple-Tasker.pdf) in the
Embedded Systems Design magazine in
[July 2006](https://www.embedded.com/embedded-systems-design-july-2006).
That original version of SST (now called "Legacy SST") is
[still available](legacy) and is provided for historical reference.

Over the years, more complete SST-like kernels have been developed
for a number of embedded processors, such as: ARM7TDMI, ARM Cortex-M (M0-M7),
ARM Cortex-R, MSP430, PIC24/dsPIC, PIC32, etc. All these kernels are now
included in the
[QP/C and QP/C++ Real-Time Embedded Frameworks](https://www.state-machine.com/products/qp):

- [QK preemptive, priority-based, non-blocking kernel](https://www.state-machine.com/qpc/srs_qk.html)
works like SST and is available as one of the built-in kernels in the
[QP Real-Time Embedded Frameworks (RTEFs)](https://www.state-machine.com/products/qp).

- [QXK preemptive, dual-mode kernel](https://www.state-machine.com/qpc/srs_qxk.html)
combines the basic-tasks of SST with traditional blocking tasks (a.k.a.
**extended tasks** in OSEK/VDX) and is available as one of the
built-in kernels in the
[QP Real-Time Embedded Frameworks (RTEFs)](https://www.state-machine.com/products/qp)

- [QV priority-based, cooperative kernel](https://www.state-machine.com/qpc/srs_qv.html)
works like [SST0](#non-preemptive-sst0) and is available as one of the built-in
kernels in the
[QP Real-Time Embedded Frameworks (RTEFs)](https://www.state-machine.com/products)


# Non-Preemptive SST0
This repository contains also the non-preemptive implementation of the
SST API, called **SST0**. SST0 is also a **priority-based RTOS kernel**,
but the scheduling is non-preemptive. SST0 scheduler always executes the
highest-priority basic task ready to run, but the scheduling is performed
only after voluntary completion of each task (run-to-completion execution).

<p align="center"><img src="img/logo_sst0-chip.png"/></p>

SST0 provides the following features:
- basic tasks (non-blocking, run-to-completion)
- priority-based, non-preemptive (cooperative) scheduling
- only one task per priority level
- multiple "activations" per task (event queues)


# Getting Started / Examples
The best way to get started with SST is to build and run the provided
**examples**. This repository contains several versions of the
**"blinky-button" example**, which contains several SST tasks running
concurrently and communicating with each other. The "blinky-button" example
demonstrates **real-time** capabilities of SST and uses a logic analyzer.
(REMARK: Logic analyzer is not necessary to build and run the examples.)

<p align="center"><img src="img/blinky_button.png"/></p>

The "blinky-button" example is provided for:
```c
Super-Simple-Tasker/
|
+---sst_c/                     // preemptive SST/C
|   +----examples/             // examples for SST/C
|   |    +----blinky_button/   // "blinky-button" example
|   |    |    +----armclang/   // project for ARM/KEIL
|   |    |    +----gnu/        // makefile for GNU-ARM
|   |    |    +----iar/        // project for IAR EWARM
|
+---sst_cpp/                   // preemptive SST/C++
|   +----examples/             // examples for SST/C++
|   |    +----blinky_button/   // "blinky-button" example
|   |    |    +----armclang/   // project for ARM/KEIL
|   |    |    +----gnu/        // makefile for GNU-ARM
|   |    |    +----iar/        // project for IAR EWARM
|
+---sst0_c/                    // non-preemptive SST0/C
|   +----examples/             // examples for SST0/C
|   |    +----blinky_button/   // "blinky-button" example
|   |    |    +----armclang/   // project for ARM/KEIL
|   |    |    +----gnu/        // makefile for GNU-ARM
|   |    |    +----iar/        // project for IAR EWARM
|
+---sst0_cpp/                  // non-preemptive SST0/C++
|   +----examples/             // examples for SST0/C++
|   |    +----blinky_button/   // "blinky-button" example
|   |    |    +----armclang/   // project for ARM/KEIL
|   |    |    +----gnu/        // makefile for GNU-ARM
|   |    |    +----iar/        // project for IAR EWARM
|
```
For **every** of these cases the projects to build the examples are provided
for the following embedded boards:

<p align="center">
<img src="img/bd-nucleos.png"/>
<img src="img/bd_EK-TM4C123GXL.jpg"/>
</p>

- **STM32 NUCLEO-C031C6** (ARM Cortex-M0+)
- **STM32 NUCLEO-L053R8** (ARM Cortex-M0+)
- **STM32 NUCLEO-H743ZI** (ARM Cortex-M7 with double-precision FPU)
- **TivaC LaunchPad (EK-TM4C123GXL)** (ARM Cortex-M4 with single-precision FPU)

# Licensing
The SST source code and examples are released under the terms of the
permissive [MIT open source license](LICENSE). Please note that the
attribution clause in the MIT license requires you to preserve the
original copyright notice in all changes and derivate works.


# Invitation to Collaborate
**This project welcomes collaboration!** Please help to improve SST,
port it to other processors, integrate it with other embedded software,
add interesting examples, etc. To avoid fragmentation, this repository is
intended to remain the home of SST. To contribute, please clone, fork,
and submit **pull requests** to incorporate your changes.


# How to Help this Project?
If you like this project, please **spread the word** about SST on various
forums, social media, and other venues frequented by embedded folks!

<p align="center"><img src="img/spread-the-word.jpg"/></p>

Also, please give [this repository](https://github.com/QuantumLeaps/Super-Simple-Tasker)
a star (in the upper-right corner of your browser window)

<p align="center"><img src="img/github-star.jpg"/></p>


## 可选的注册投递时间事件（SST/C）

静态链表负责倒计时、周期重装和到期交付；投递 operations 由使用者
注册，可面向普通线程收件箱。原有 `SST_TimeEvt_*` 仍固定面向 AO，
两者各有独立链表和 tick 入口，互不自动驱动。

与 `sst_pubsub` 一样按源文件选择启用：包含 `sst_time_evt.h`，将
`sst_c/src/sst_time_evt.c` 加入工程，并显式驱动 `TimeEvt_tick()`。
`sst.h`、`SST_init()` 和原有 tick 不引用本模块；不用时无需加入源文件，
也不增加节点或链表存储。保留 `TimeEvt_*` API，避免与 AO 时间事件混淆。

- 接口：`include/sst_time_evt.h`
- 实现：`sst_c/src/sst_time_evt.c`
- 宿主测试及示例 port：`tests/time_evt/`

### 注册、计时与交付

```c
static unsigned const event = 42U;
static TimeEvt timer;

static void deliver(void *context, void const *event) {
    /* 使用 context 向接收方入列；由适配端解释事件类型。 */
}

static TimeEvt_PostOperations const delivery = {
    .context = NULL,
    .post = deliver
};

/* 在并发运行之前，只构造、注册一次。 */
TimeEvt_ctor(&timer, &event, &delivery);

/* 第 150 拍单次到期；若驱动频率为 100 Hz，名义延时为 1.5 s。 */
TimeEvt_arm(&timer, 150U, 0U);

/* 由外部单一驱动者周期调用，不允许重入。 */
TimeEvt_tick();

/* 停止后续到期；返回此前是否仍在计时。 */
(void)TimeEvt_disarm(&timer);
```

`delay` 必须大于零。`interval=0` 为单次，正数为周期；例如 `(1,1)`
每拍到期，`(2,4)` 在第二拍首次到期，此后每四拍到期。重新 arm 替换
当前倒计时，首次递减发生在下一拍，因此存在一拍的相位不确定性。

节点借用不透明的 `void const *event`，不解析、不修改、不分配或回收。
节点、非空事件、operations 及 context 必须覆盖计时与排队交付的完整
生命周期。构造完成后不允许复制节点、修改其成员、重新绑定或注销。
静态事件的信号、引用计数及 GC 规则均由使用者负责。

交付回调在临界区外执行，需要及时返回，不能递归驱动 tick 或修改
注册链表；可以在遵守 port 同步约定的前提下调用 arm/disarm。
同一拍内跨节点的回调执行顺序不作为业务契约。

### Port 契约

复用使用方的 `sst_port.h` 和 SST 的 `dbc_assert.h`：

| 宏 | 职责 |
|---|---|
| `DBC_REQUIRE(label, condition)` | 契约失败时停止执行，不能忽略后继续 |
| `SST_PORT_CRIT_STAT` | 声明临界区所需的局部状态，允许展开为空 |
| `SST_PORT_CRIT_ENTRY()` | 序列化共享计数的读写 |
| `SST_PORT_CRIT_EXIT()` | 恢复进入前的同步状态 |

port 必须保证计数更新之间的互斥与内存可见性；ISR 是否能调用
arm/disarm 也由 port 决定。仅在完全串行使用时，临界区才可为空实现。
模块不默认关闭断言或使用空锁。测试 port 展示了状态保存/恢复的形状，
用于宿主顺序及交错测试，不是可直接用于多线程互斥的实现。

到期在临界区内提交，之后才调用 post。因此 disarm 不能撤回已提交
的到期，即使回调尚未执行；也不撤回已入列的消息。重新 arm 同样不
撤回旧消息。需要取消后重新进入等业务协议时，由使用者处理旧消息。

### 宿主验证

在仓库根目录运行，产物写到 `/tmp`：

```sh
gcc -std=c11 -Wall -Wextra -Werror \
  -fsanitize=address,undefined -fno-pie -no-pie \
  -Iinclude -Itests/time_evt \
  sst_c/src/sst_time_evt.c tests/time_evt/test_time_evt.c \
  -o /tmp/sst-time-evt-test
/tmp/sst-time-evt-test
```

覆盖不同事件类型和接收方、单次/周期、重 arm、disarm、到期与取消
交错，以及重复注册等契约。sm_blinky 的普通 UI 线程使用该模块。
