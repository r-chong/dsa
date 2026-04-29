class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        # sentinel
        heights.append(0)

        # increasing
        ms = []
        n = len(heights)
        best = 0

        # we compute left smallest rect and right smallest rect
        for i in range(n):
            while ms and heights[i] < heights[ms[-1]]:
                # i is right due to loop constraints
                # lsi is top of stack only if stack exists, otherwise latest element (all indices)
                top_i = ms.pop()
                height = heights[top_i]

                lsi = ms[-1] if ms else -1
                width = i - lsi - 1

                best = max(best, height * width)

            ms.append(i)
        
        heights.pop()
        return best
