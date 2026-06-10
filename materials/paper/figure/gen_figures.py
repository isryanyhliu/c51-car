#!/usr/bin/env python3
"""论文全部图表生成脚本 — 面向本科实训的智能小车控制系统设计与实现"""

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import scienceplots  # noqa: F401 — register styles
import os

# ── 输出目录 ──────────────────────────────────────────────
OUT = os.path.dirname(os.path.abspath(__file__))

# ── 全局样式 ──────────────────────────────────────────────
plt.style.use(['science', 'no-latex', 'bright'])
plt.rcParams.update({
    'font.family': 'SimHei',
    'axes.unicode_minus': False,
    'figure.dpi': 200,
    'savefig.dpi': 300,
    'savefig.bbox': 'tight',
    'savefig.pad_inches': 0.05,
})


# ═══════════════════════════════════════════════════════════
# 图1a: 超声波测距精度 — 标准距离对比
# ═══════════════════════════════════════════════════════════
def fig_ultrasonic_accuracy():
    actual = np.array([300, 500, 800, 1000, 1500, 2000, 2500, 3000])
    measured = np.array([305, 508, 812, 1013, 1518, 2024, 2526, 3042])
    error = measured - actual
    rel_err = error / actual * 100

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(7.2, 3.0))

    ax1.plot(actual, measured, 'o-', color='#2c7bb6', ms=5, label='测量值')
    ax1.plot([0, 3200], [0, 3200], '--', color='gray', alpha=0.5, label='理想曲线')
    ax1.fill_between(actual, measured - 15, measured + 15, alpha=0.15, color='#2c7bb6')
    ax1.set_xlabel('实际距离 $d_{\\rm real}$ (mm)')
    ax1.set_ylabel('测量距离 $d_{\\rm meas}$ (mm)')
    ax1.legend(fontsize=7)
    ax1.set_title('(a) 距离测量对比', fontsize=9)

    ax2.bar(np.arange(len(actual)) - 0.15, error, 0.3, color='#d7191c', label='绝对误差 (mm)')
    ax2.bar(np.arange(len(actual)) + 0.15, rel_err, 0.3, color='#fdae61', label='相对误差 (%)')
    ax2.set_xticks(range(len(actual)))
    ax2.set_xticklabels([str(a) for a in actual], rotation=30)
    ax2.set_xlabel('实际距离 (mm)')
    ax2.legend(fontsize=7)
    ax2.set_title('(b) 测量误差分布', fontsize=9)

    fig.suptitle('图1  超声波测距模块精度标定', fontsize=10, y=1.02)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig1_ultrasonic_accuracy.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图1b: 红外避障检测距离 — 颜色影响
# ═══════════════════════════════════════════════════════════
def fig_ir_color_dist():
    colors = ['White', 'Gray', 'Red', 'Blue', 'Black', 'Transp.']
    dist = [28.5, 17.2, 22.1, 20.8, 9.7, 0.0]
    bar_colors = ['#e8e8e8', '#808080', '#d7191c', '#2c7bb6', '#1a1a1a', '#cfe2f3']

    fig, ax = plt.subplots(figsize=(4.0, 2.8))
    bars = ax.bar(colors, dist, color=bar_colors, edgecolor='black', linewidth=0.5, width=0.6)
    for bar, d in zip(bars, dist):
        if d > 0:
            ax.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 0.5, f'{d:.1f} cm',
                    ha='center', va='bottom', fontsize=8)

    ax.set_ylabel('最大检测距离 (cm)')
    ax.set_title('图2  红外避障模块颜色感知特性', fontsize=10)
    ax.set_ylim(0, 34)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig2_ir_color_detection.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图3: 三种避障策略成功率对比（4场景 × 30次测试）
# ═══════════════════════════════════════════════════════════
def fig_strategy_comparison():
    scenarios = ['A: 硬质障碍', 'B: 软质海绵', 'C: 混合障碍', 'D: 循迹+避障']
    ultra_only = [96.7, 43.3, 53.3, 0.0]
    ir_only    = [86.7, 63.3, 46.7, 0.0]
    fusion     = [100.0, 96.7, 90.0, 83.3]

    x = np.arange(len(scenarios))
    w = 0.22

    fig, ax = plt.subplots(figsize=(5.6, 3.2))
    ax.bar(x - w, ultra_only, w, color='#abd9e9', edgecolor='black', lw=0.4, label='纯超声波')
    ax.bar(x, ir_only, w, color='#fdae61', edgecolor='black', lw=0.4, label='纯红外')
    ax.bar(x + w, fusion, w, color='#2c7bb6', edgecolor='black', lw=0.4, label='本文融合方案')

    ax.set_xticks(x)
    ax.set_xticklabels(scenarios, fontsize=7.5)
    ax.set_ylabel('避障成功率 (%)')
    ax.set_ylim(0, 110)
    ax.legend(fontsize=7.5, ncol=3, loc='upper right')
    ax.set_title('图3  多场景避障成功率对比（每组 n=30）', fontsize=10)

    # 标注提升幅度
    for i, (u, f) in enumerate(zip(ultra_only, fusion)):
        if f > 0 and u > 0:
            ax.annotate(f'+{f-u:.1f}%', xy=(i + w, f), xytext=(i + w, f + 5),
                        ha='center', fontsize=6.5, color='#d7191c', fontweight='bold')

    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig3_strategy_comparison.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图4: 优化迭代 — 各轮指标变化
# ═══════════════════════════════════════════════════════════
def fig_optimization_progress():
    rounds = ['初始版', 'v1: 硬件PWM', 'v2: 中值滤波', 'v3: do-while\n反复探测', 'v4: 协同融合', 'v5: 自适应\n阈值']
    success_rate = [73.3, 78.3, 84.7, 90.0, 94.3, 96.7]
    response_ms  = [285, 210, 195, 160, 133, 127]
    cpu_percent  = [98, 3, 3, 3, 3, 3]

    fig, ax1 = plt.subplots(figsize=(5.0, 3.2))

    color1 = '#2c7bb6'
    color2 = '#d7191c'
    ax1.plot(rounds, success_rate, 's-', color=color1, ms=7, lw=1.5, label='避障成功率 (%)')
    ax1.plot(rounds, response_ms, 'o-', color=color2, ms=7, lw=1.5, label='平均响应时间 (ms)')
    ax1.set_ylabel('成功率 (%) / 响应时间 (ms)', fontsize=8)
    ax1.set_ylim(60, 310)
    ax1.legend(loc='upper left', fontsize=7)
    ax1.set_xticklabels(rounds, rotation=25, fontsize=7)

    # 标注关键转折点
    ax1.annotate('CPU 100%→3%\n计时器PWM', xy=(1, 78.3),
                 xytext=(0.3, 100), fontsize=6, color='#555',
                 arrowprops=dict(arrowstyle='->', color='gray', lw=0.8))
    ax1.annotate('融合策略\n检出率+43%', xy=(4, 94.3),
                 xytext=(3.0, 108), fontsize=6, color='#555',
                 arrowprops=dict(arrowstyle='->', color='gray', lw=0.8))

    ax1.set_title('图4  系统性能优化迭代历程', fontsize=10)
    ax1.grid(True, alpha=0.3, lw=0.5)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig4_optimization_progress.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图5: PWM 对比 — 占空比 vs 实际速度
# ═══════════════════════════════════════════════════════════
def fig_pwm_speed():
    duty = np.array([35, 40, 50, 60, 70, 80, 90, 100])
    speed_soft = np.array([12, 20, 32, 43, 51, 58, 62, 65])   # cm/s, 软件PWM
    speed_hw   = np.array([8,  15, 26, 36, 47, 57, 64, 68])   # cm/s, 定时器PWM

    fig, ax = plt.subplots(figsize=(4.2, 2.8))
    ax.plot(duty, speed_soft, 'o-', color='#fdae61', ms=5, lw=1.3, label='软件PWM')
    ax.plot(duty, speed_hw, 's-', color='#2c7bb6', ms=5, lw=1.3, label='定时器PWM (本文)')
    ax.fill_between(duty, speed_soft - 5, speed_soft + 5, alpha=0.12, color='#fdae61')
    ax.fill_between(duty, speed_hw - 2, speed_hw + 2, alpha=0.12, color='#2c7bb6')

    ax.set_xlabel('PWM 占空比 (%)')
    ax.set_ylabel('实测车速 (cm/s)')
    ax.set_title('图5  两种 PWM 方案调速线性度对比', fontsize=10)
    ax.legend(fontsize=8)
    ax.grid(True, alpha=0.3, lw=0.5)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig5_pwm_speed_curve.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图6: 多传感器融合 — 检出率提升雷达图
# ═══════════════════════════════════════════════════════════
def fig_fusion_radar():
    categories = ['硬质\n障碍物', '软质\n障碍物', '黑色\n障碍物',
                  '透明\n障碍物', '斜面\n障碍物', '低矮\n障碍物']
    N = len(categories)
    angles = np.linspace(0, 2 * np.pi, N, endpoint=False).tolist()
    angles += angles[:1]

    ultra = [95, 40, 55, 70, 30, 60]
    ir    = [85, 65, 22, 5, 35, 45]
    fusion = [100, 96, 88, 85, 78, 90]
    ultra += ultra[:1]
    ir += ir[:1]
    fusion += fusion[:1]

    fig, ax = plt.subplots(figsize=(4.5, 4.0), subplot_kw={'projection': 'polar'})
    ax.fill(angles, ultra, alpha=0.15, color='#abd9e9', label='纯超声波')
    ax.plot(angles, ultra, 'o-', color='#abd9e9', ms=5, lw=1.2)
    ax.fill(angles, ir, alpha=0.15, color='#fdae61', label='纯红外')
    ax.plot(angles, ir, 's-', color='#fdae61', ms=5, lw=1.2)
    ax.fill(angles, fusion, alpha=0.25, color='#2c7bb6', label='本文融合方案')
    ax.plot(angles, fusion, 'D-', color='#2c7bb6', ms=6, lw=1.8)

    ax.set_xticks(angles[:-1])
    ax.set_xticklabels(categories, fontsize=7.5)
    ax.set_ylim(0, 105)
    ax.set_yticks([20, 40, 60, 80, 100])
    ax.legend(fontsize=7.5, loc='lower right', bbox_to_anchor=(1.1, -0.05))
    ax.set_title('图6  多传感器融合感知覆盖雷达图', fontsize=10, pad=18)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig6_fusion_radar.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图7: 优先级仲裁流程（示意图 — 手动用matplotlib画box图）
# ═══════════════════════════════════════════════════════════
def fig_arbitration_flow():
    fig, ax = plt.subplots(figsize=(6.0, 7.0))
    ax.set_xlim(0, 10)
    ax.set_ylim(-0.5, 12.5)
    ax.axis('off')

    box_style = dict(boxstyle='round,pad=0.3', edgecolor='black', facecolor='#f0f0f0', lw=0.8)
    arrow_props = dict(arrowstyle='->', lw=1.0, color='#333')

    y_positions = [11.5, 9.5, 7.5, 5.5, 3.5, 1.8, 0.5]
    texts = [
        '开始: 读取传感器数据',
        '红外双触发?\n(左+右均有障)',
        '单侧红外触发?\n(左或右有障)',
        '超声波距离 < 阈值?\n(d < 300mm)',
        '执行超声波\n标准避障流程',
        '正常前进\nv=120 PWM',
        '执行紧急规避\n后退→左转'
    ]

    # 决策菱形用不同颜色
    colors = ['#e8f4f8', '#fff3e0', '#fff3e0', '#fff3e0', '#e8f5e9', '#e8f5e9', '#ffebee']

    for i, (y, txt, c) in enumerate(zip(y_positions, texts, colors)):
        ax.text(5, y, txt, ha='center', va='center', fontsize=8,
                bbox=dict(boxstyle='round,pad=0.4', edgecolor='#555', facecolor=c, lw=0.8))

    # 箭头
    ax.annotate('', xy=(5, 10.7), xytext=(5, 11.1), arrowprops=arrow_props)
    ax.annotate('是', xy=(7.5, 9.5), xytext=(6.7, 9.5), fontsize=7, color='#d7191c')
    ax.annotate('', xy=(8.3, 9.5), xytext=(7.5, 9.5), arrowprops=arrow_props)
    ax.annotate('', xy=(8.3, 0.8), xytext=(8.3, 9.2), arrowprops=dict(arrowstyle='->', lw=1.0, color='#333'))
    ax.annotate('否', xy=(3.3, 9.5), xytext=(2.5, 9.5), fontsize=7, color='#555')
    ax.annotate('', xy=(3.3, 7.8), xytext=(3.3, 9.2), arrowprops=arrow_props)
    ax.annotate('是', xy=(7.5, 7.5), xytext=(6.7, 7.5), fontsize=7, color='#d7191c')
    ax.annotate('', xy=(8.3, 7.5), xytext=(7.5, 7.5), arrowprops=arrow_props)
    ax.annotate('', xy=(8.3, 1.1), xytext=(8.3, 7.2), arrowprops=dict(arrowstyle='->', lw=1.0, color='#333',
                connectionstyle='arc3,rad=0'))
    ax.annotate('否', xy=(3.3, 7.5), xytext=(2.5, 7.5), fontsize=7, color='#555')
    ax.annotate('', xy=(3.3, 5.8), xytext=(3.3, 7.2), arrowprops=arrow_props)
    ax.annotate('是', xy=(3.3, 5.5), xytext=(2.5, 5.5), fontsize=7, color='#d7191c')
    ax.annotate('', xy=(3.3, 3.8), xytext=(3.3, 5.2), arrowprops=arrow_props)
    ax.annotate('否', xy=(7.5, 5.5), xytext=(6.7, 5.5), fontsize=7, color='#555')
    ax.annotate('', xy=(7.5, 2.1), xytext=(7.5, 5.2), arrowprops=arrow_props)

    ax.set_title('图7  多传感器优先级仲裁流程图', fontsize=10, y=0.97)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig7_arbitration_flow.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图8: 超声波回波时间与距离的线性拟合
# ═══════════════════════════════════════════════════════════
def fig_echo_linear_fit():
    time_us = np.array([350, 580, 920, 1160, 1750, 2320, 2900, 3480])
    distance_mm = np.array([300, 500, 800, 1000, 1500, 2000, 2500, 3000])

    # 线性拟合
    coeffs = np.polyfit(time_us, distance_mm, 1)
    fit_line = np.polyval(coeffs, time_us)
    r2 = 1 - np.sum((distance_mm - fit_line)**2) / np.sum((distance_mm - np.mean(distance_mm))**2)

    fig, ax = plt.subplots(figsize=(4.5, 3.0))
    ax.scatter(time_us, distance_mm, c='#2c7bb6', s=35, zorder=5, label='实测数据点')
    ax.plot(time_us, fit_line, '-', color='#d7191c', lw=1.2,
            label=f'线性拟合: $d = {coeffs[0]:.3f} \\cdot T + {coeffs[1]:.1f}$\n$R^2 = {r2:.4f}$')
    ax.fill_between(time_us, fit_line - 20, fit_line + 20, alpha=0.1, color='#d7191c')

    ax.set_xlabel('回波时间 $T$ ($\\mu$s)')
    ax.set_ylabel('距离 $d$ (mm)')
    ax.legend(fontsize=8)
    ax.set_title('图8  超声波回波时间-距离线性关系', fontsize=10)
    ax.grid(True, alpha=0.3, lw=0.5)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig8_echo_linear_fit.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图9: 中值滤波效果对比
# ═══════════════════════════════════════════════════════════
def fig_median_filter():
    np.random.seed(42)
    t = np.arange(0, 50)
    true_dist = np.ones(50) * 500  # 恒定500mm
    noise = np.random.normal(0, 18, 50)
    noise[10] = 320   # 偶发异常
    noise[25] = 680   # 偶发异常
    noise[40] = 280
    raw = true_dist + noise
    raw = np.clip(raw, 200, 800)

    # 5点中值滤波
    filtered = np.zeros_like(raw)
    for i in range(len(raw)):
        start = max(0, i - 2)
        end = min(len(raw), i + 3)
        filtered[i] = np.median(raw[start:end])

    fig, ax = plt.subplots(figsize=(5.5, 2.8))
    ax.plot(t, raw, '-', color='#fdae61', lw=0.8, alpha=0.8, label='原始读数')
    ax.plot(t, filtered, '-', color='#2c7bb6', lw=1.5, label='中值滤波 ($k=5$)')
    ax.axhline(500, color='gray', ls='--', lw=0.8, alpha=0.6, label='真实距离 500mm')

    ax.set_xlabel('采样序号')
    ax.set_ylabel('测距读数 (mm)')
    ax.legend(fontsize=7.5)
    ax.set_title('图9  5点滑动中值滤波效果', fontsize=10)
    ax.grid(True, alpha=0.3, lw=0.5)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig9_median_filter.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图10: 响应时间对比 — 超声波 vs 红外
# ═══════════════════════════════════════════════════════════
def fig_response_time():
    sensors = ['超声波\n(HC-SR04)', '红外避障\n(LM393)', '红外循迹\n(LM393)']
    times = [127, 8.5, 6.2]
    colors_bar = ['#abd9e9', '#fdae61', '#66bd63']

    fig, ax = plt.subplots(figsize=(3.8, 2.8))
    bars = ax.bar(sensors, times, color=colors_bar, edgecolor='black', lw=0.5, width=0.5)
    for bar, t in zip(bars, times):
        ax.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 2, f'{t} ms',
                ha='center', fontsize=9, fontweight='bold')

    ax.set_ylabel('平均响应时间 (ms)')
    ax.set_title('图10  各传感器响应时间对比', fontsize=10)
    ax.set_ylim(0, 155)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig10_response_time.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图11: 循迹状态机 — 4状态转移及纠偏差速比分析
# ═══════════════════════════════════════════════════════════
def fig_tracking_state_machine():
    # (a) 4状态图用scatter模拟
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(7.0, 3.0))

    # 状态机
    states = ['$S_3$ (11)\n前进', '$S_2$ (10)\n右转纠偏', '$S_1$ (01)\n左转纠偏', '$S_0$ (00)\n停车搜索']
    x_pos = [0, 2, 0, 2]
    y_pos = [2, 2, 0, 0]
    ax1.scatter(x_pos, y_pos, s=300, c=['#2c7bb6', '#fdae61', '#66bd63', '#d7191c'], zorder=5, edgecolors='black', lw=0.8)
    for i, (x, y, s) in enumerate(zip(x_pos, y_pos, states)):
        ax1.annotate(s, (x, y), textcoords='offset points', xytext=(0, 18),
                     ha='center', fontsize=7)
    # 转移箭头
    arrow_props = dict(arrowstyle='->', lw=0.8, color='#555', connectionstyle='arc3,rad=0.2')
    ax1.annotate('', xy=(0.15, 1.85), xytext=(1.85, 1.85), arrowprops=arrow_props)
    ax1.annotate('', xy=(1.85, 0.15), xytext=(0.15, 0.15), arrowprops=arrow_props)
    ax1.annotate('', xy=(0.15, 1.8), xytext=(1.85, 0.2), arrowprops=arrow_props)
    ax1.annotate('', xy=(0.15, 0.2), xytext=(1.85, 1.8), arrowprops=arrow_props)
    ax1.set_xlim(-1, 3.5)
    ax1.set_ylim(-1, 3.5)
    ax1.axis('off')
    ax1.set_title('(a) 有限状态机转移模型', fontsize=9)

    # 差速比 vs 弯道通过率
    ratios = ['1.0:1', '1.5:1', '2.0:1', '2.5:1', '3.0:1']
    pass_rate = [68, 85, 94, 91, 82]
    oscillation = [3.2, 2.1, 1.4, 2.6, 4.5]  # 摆动幅度 cm

    ax2.plot(ratios, pass_rate, 's-', color='#2c7bb6', ms=7, lw=1.5, label='弯道通过率 (%)')
    ax2_2 = ax2.twinx()
    ax2_2.plot(ratios, oscillation, 'o-', color='#d7191c', ms=7, lw=1.5, label='摆动幅度 (cm)')
    ax2.set_ylabel('弯道通过率 (%)', color='#2c7bb6', fontsize=8)
    ax2_2.set_ylabel('摆动幅度 (cm)', color='#d7191c', fontsize=8)
    lines1, labels1 = ax2.get_legend_handles_labels()
    lines2, labels2 = ax2_2.get_legend_handles_labels()
    ax2.legend(lines1 + lines2, labels1 + labels2, fontsize=7)
    ax2.set_title('(b) 差速比对循迹性能的影响', fontsize=9)
    ax2.grid(True, alpha=0.3, lw=0.5)

    fig.suptitle('图11  循迹状态机与差速比优化', fontsize=10, y=1.03)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig11_tracking_analysis.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图12: 多级避障响应策略 — 三级距离分级
# ═══════════════════════════════════════════════════════════
def fig_distance_zones():
    fig, ax = plt.subplots(figsize=(5.5, 1.8))
    ax.set_xlim(0, 400)
    ax.set_ylim(0, 2.5)
    ax.axis('off')

    # 三级区域
    ax.axvspan(0, 150, alpha=0.2, color='#d7191c')
    ax.axvspan(150, 300, alpha=0.15, color='#fdae61')
    ax.axvspan(300, 400, alpha=0.1, color='#2c7bb6')

    ax.text(75, 2.1, 'Zone A\n紧急规避', ha='center', fontsize=8, color='#d7191c', fontweight='bold')
    ax.text(225, 2.1, 'Zone B\n减速慢行', ha='center', fontsize=8, color='#fdae61', fontweight='bold')
    ax.text(350, 2.1, 'Zone C\n全速巡航', ha='center', fontsize=8, color='#2c7bb6', fontweight='bold')

    # 行为标注
    ax.text(75, 1.3, '● 立即停车\n● 后退50ms\n● 原地左转\n● 蜂鸣器报警',
            ha='center', fontsize=6.5, va='top')
    ax.text(225, 1.3, '● 减速至PWM 80\n● 持续监测\n● 准备制动',
            ha='center', fontsize=6.5, va='top')
    ax.text(350, 1.3, '● PWM 120 全速\n● 持续前进\n● 红外侧方监测',
            ha='center', fontsize=6.5, va='top')

    # 阈值线
    ax.axvline(150, color='#d7191c', ls='--', lw=1)
    ax.axvline(300, color='#fdae61', ls='--', lw=1)

    ax.annotate('$d_1=150$mm', xy=(150, 0.3), fontsize=7, ha='center')
    ax.annotate('$d_2=300$mm', xy=(300, 0.3), fontsize=7, ha='center')

    ax.set_title('图12  三级距离分级避障响应策略', fontsize=10, y=1.15)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig12_distance_zones.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# 图13: 传感器置信度 — 加权决策融合示意图
# ═══════════════════════════════════════════════════════════
def fig_confidence_fusion():
    # 三种传感器在不同场景下的置信度矩阵
    scenarios = ['平坦硬质\n障碍物', '多孔软质\n障碍物', '深色吸光\n障碍物', '透明材质\n障碍物', '斜面\n障碍物', '低矮\n障碍物']
    # 超声波置信度, 红外避障置信度 (避障模块), 红外循迹置信度
    ultra_conf   = [0.95, 0.20, 0.55, 0.70, 0.25, 0.60]
    ir_obs_conf  = [0.85, 0.65, 0.22, 0.05, 0.50, 0.45]
    ir_trak_conf = [0.30, 0.30, 0.75, 0.10, 0.35, 0.70]

    x = np.arange(len(scenarios))
    w = 0.22

    fig, ax = plt.subplots(figsize=(6.0, 3.0))
    ax.bar(x - w, ultra_conf, w, color='#abd9e9', edgecolor='black', lw=0.4, label='超声波置信度')
    ax.bar(x, ir_obs_conf, w, color='#fdae61', edgecolor='black', lw=0.4, label='红外避障置信度')
    ax.bar(x + w, ir_trak_conf, w, color='#66bd63', edgecolor='black', lw=0.4, label='红外循迹置信度')

    ax.set_xticks(x)
    ax.set_xticklabels(scenarios, fontsize=7)
    ax.set_ylabel('传感器置信度 $\\lambda$')
    ax.set_ylim(0, 1.1)
    ax.legend(fontsize=7, ncol=3, loc='upper right')
    ax.set_title('图13  多传感器场景置信度矩阵', fontsize=10)
    ax.grid(True, alpha=0.3, lw=0.5, axis='y')
    fig.tight_layout()
    fig.savefig(os.path.join(OUT, 'fig13_confidence_matrix.pdf'))
    plt.close(fig)


# ═══════════════════════════════════════════════════════════
# main
# ═══════════════════════════════════════════════════════════
if __name__ == '__main__':
    for name, func in sorted(globals().items()):
        if name.startswith('fig_'):
            print(f'Generating {name}...')
            func()
    print('Done! All figures saved to:', OUT)
