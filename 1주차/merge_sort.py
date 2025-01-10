words = [
    '20211558', 'hut', 'apostle', 'equipment', 'fop', 'refined', 'parapet', 'mog', 'amputate', 'covetous', 'somebody',
    'all', 'lobbyist', 'remark', 'subscriber', 'quorum', 'steppe', 'clean', 'cu', 'commend', 'prosy',
    'supererogation', 'indignation', 'wolverine', 'emporium', 'intersect', 'constitution', 'miscast', 'rabbi', 'enmity', 'loft',
    'temporize', 'speedboat', 'agenda', 'delusion', 'class01', 'idolize', 'romance', 'overestimate', 'revive', 'smell',
    'toast', 'singe', 'inlay', 'field', 'speed', 'farad', 'adult', 'pansy', 'crawl', 'smith', 'exude',
    'froze', 'litho', 'inuit', 'fakir', 'noddy', 'sheen', 'sandy', 'gaffe', 'spark', 'cavil', 'tenor',
    'clonk', 'stung', 'boult', 'inapt', 'taker', 'cliff', 'shine', 'sable', 'agile', 'evens', 'pluck',
    'blade', 'niece', 'paste', 'theft', 'young', 'bonny', 'aggro', 'bevel', 'rebel', 'clown', 'quote',
    'horsy', 'wrong', 'hindu', 'acute', 'sloop', 'tuner', 'expel', 'motel', 'divan', 'gesso', 'strop',
    'lance', 'lifer', 'dunce', 'lemur', 'scree', 'basic', 'wring', 'graph', 'conch', 'favor', 'anise',
    'value', 'queue', 'poppy', 'staid', 'snook', 'spurt', 'canto', 'sprat', 'first', 'sidle', 'douse'
]

import random

def mergeSort(arr):
    if len(arr) < 2: return arr

    mid = len(arr) // 2
    low_arr = mergeSort(arr[:mid]) #blank
    high_arr = mergeSort(arr[mid:]) #blank

    merge_arr = []
    low_idx = high_idx = 0
    while low_idx < len(low_arr) and high_idx < len(high_arr):
        if low_arr[low_idx] < high_arr[high_idx]: #blank
            merge_arr.append(low_arr[low_idx])
            low_idx += 1
        else:
            merge_arr.append(high_arr[high_idx])
            high_idx += 1

    merge_arr += low_arr[low_idx:] #blank
    merge_arr += high_arr[high_idx:] #blank
    
    return merge_arr

merged_words = mergeSort(words)
print(merged_words)
