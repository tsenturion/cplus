class IsNegativeException {};
class IsZeroException {};

void CheckValue(int x) {
    if (x < 0) throw IsNegativeException();
    if (x == 0) throw IsZeroException();
}

int main() {
    try {
        CheckValue(-1);
        CheckValue(0);
        CheckValue(1);
    } catch (IsNegativeException) {
        std::cout << "Negative value\n";
    } catch (IsZeroException) {
        std::cout << "Zero value\n";
    }
    return 0;


