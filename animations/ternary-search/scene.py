import manim as m
import numpy as np

from manim.utils.unit import Percent
from typing import Union


def f(x):
    return (x + 0.768) ** 2 - 6


class TernarySearch(m.Scene):
    N_ITERATIONS = 4

    @staticmethod
    def _build_line(value: float) -> m.Line:
        start = np.array([value, 0, 0])
        end = np.array([value, f(value), 0])
        return m.Line(start=start, end=end)

    @staticmethod
    def _add_text_to_line(pos: float, line: m.Line, text: Union[m.Text, m.MathTex]):
        text.next_to(line, m.UP if f(pos) < 0 else m.DOWN)

    def _make_line_and_text(self, pos: float, text: str):
        line = self._build_line(pos)
        mtext = m.MathTex(text).scale(0.7)
        self._add_text_to_line(pos, line, mtext)
        return line, mtext

    def _ternary_search(self, left, right):
        right_line, right_text = self._make_line_and_text(right, "x_{max}")
        left_line, left_text = self._make_line_and_text(left, "x_{min}")

        self.play(m.Create(left_line), m.Create(right_line))
        self.play(m.Create(left_text), m.Create(right_text))

        for _ in range(self.N_ITERATIONS):
            third = (right - left) / 3
            m1 = left + third
            m2 = right - third

            m1_line, m1_text = self._make_line_and_text(m1, "m_1")
            m2_line, m2_text = self._make_line_and_text(m2, "m_2")

            self.play(m.Create(m1_line), m.Create(m2_line))
            self.play(m.Create(m1_text), m.Create(m2_text))

            if f(m1) > f(m2):
                selected_line, selected_text = self._make_line_and_text(m1, "m_1")
                selected_line.set_color(m.YELLOW)
                selected_text.set_color(m.YELLOW)

                self.play(
                    m.Transform(m1_line, selected_line),
                    m.Transform(m1_text, selected_text),
                )
                self.play(m.FadeOut(left_line), m.FadeOut(left_text))

                left = m1
                left_line, left_text = self._make_line_and_text(left, "x_{min}")
                self.play(
                    m.Transform(m1_line, left_line), m.Transform(m1_text, left_text)
                )
                # Account for bug in Manin where Transform moves the reference
                left_line, left_text = m1_line, m1_text

                self.play(m.FadeOut(m2_line), m.FadeOut(m2_text))
            else:
                selected_line, selected_text = self._make_line_and_text(m2, "m_2")
                selected_line.set_color(m.YELLOW)
                selected_text.set_color(m.YELLOW)

                self.play(
                    m.Transform(m2_line, selected_line),
                    m.Transform(m2_text, selected_text),
                )
                self.play(m.FadeOut(right_line), m.FadeOut(right_text))

                right = m2
                right_line, right_text = self._make_line_and_text(right, "x_{max}")
                self.play(
                    m.Transform(m2_line, right_line), m.Transform(m2_text, right_text)
                )
                # Account for bug in Manin where Transform moves the reference
                right_line, right_text = m2_line, m2_text

                self.play(m.FadeOut(m1_line), m.FadeOut(m1_text))

    def construct(self):
        # Draw Title
        title = m.Text("Busca\nTernária", font="Ubuntu").scale(1.5)
        title.move_to(40 * Percent(m.Y_AXIS) * m.UP + 25 * Percent(m.X_AXIS) * m.LEFT)
        # Draw axes
        axes = m.Axes()
        self.play(m.FadeIn(title, run_time=1), m.Create(axes, run_time=2))
        # Draw function
        function = m.FunctionGraph(f)
        self.play(m.Create(function))

        # Draw left and right values
        left, right = -3, 3
        self._ternary_search(left, right)
        self.wait(10)
