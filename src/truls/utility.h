float remap (float value, float from1, float to1, float from2, float to2) {
    float result = (value - from1) / (to1 - from1) * (to2 - from2) + from2;
    result = min(result, to2);
    result = max(result, from2);
    return result;
}



