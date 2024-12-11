import pandas as pd
import re

def parse_line(line):
    """Parse a single line of data, handling multiple tabs between values."""
    # Split by tabs and filter out empty strings
    parts = [p for p in line.split('\t') if p.strip()]
    if len(parts) >= 8:  # We expect 9 values (size + 4 pairs of comp/time)
        try:
            return {
                'Size': int(parts[0]),
                'Bubble Sort Comps': int(parts[1]),
                'Bubble Sort Time': float(parts[2]),
                'Selection Sort Comps': int(parts[3]),
                'Selection Sort Time': float(parts[4]),
                'Insertion Sort Comps': int(parts[5]),
                'Insertion Sort Time': float(parts[6]),
                'Heap Sort Comps': int(parts[7]),
                'Heap Sort Time': float(parts[8])
            }
        except (ValueError, IndexError):
            return None
    return None

def parse_output(output):
    sections = {}
    current_section = None
    data = []
    
    for line in output.strip().split('\n'):
        if '===' in line:
            if current_section and data:
                sections[current_section] = data
            current_section = line.strip('= ')
            data = []
        elif line.strip() and not 'Size\tBubble' in line and not 'Comps\tTime' in line:
            parsed = parse_line(line)
            if parsed:
                data.append(parsed)
    
    if current_section and data:
        sections[current_section] = data
    
    # Convert to DataFrames with array type information
    all_data = []
    for section, rows in sections.items():
        array_type = section.replace(' Array Results', '')
        for row in rows:
            row_with_type = row.copy()
            row_with_type['Array Type'] = array_type
            all_data.append(row_with_type)
    
    if all_data:
        df = pd.DataFrame(all_data)
        
        # Create separate DataFrames for comparisons and runtime
        comps_cols = ['Array Type', 'Size'] + [col for col in df.columns if 'Comps' in col]
        time_cols = ['Array Type', 'Size'] + [col for col in df.columns if 'Time' in col]
        
        df_comps = df[comps_cols].copy()
        df_time = df[time_cols].copy()
        
        # Rename columns to remove the type suffix
        df_comps.columns = [col.replace(' Comps', '') for col in df_comps.columns]
        df_time.columns = [col.replace(' Time', '') for col in df_time.columns]
        
        # Sort by Array Type and Size
        df_comps = df_comps.sort_values(['Array Type', 'Size'])
        df_time = df_time.sort_values(['Array Type', 'Size'])
        
        return {
            'comparisons': df_comps,
            'time': df_time
        }
    
    return None

def create_excel_files(dfs):
    if dfs:
        # Save comparisons to Excel
        with pd.ExcelWriter('sorting_comparisons.xlsx') as writer:
            dfs['comparisons'].to_excel(writer, sheet_name='All Arrays', index=False)
        
        # Save runtimes to Excel
        with pd.ExcelWriter('sorting_runtimes.xlsx') as writer:
            dfs['time'].to_excel(writer, sheet_name='All Arrays', index=False)

def main():
    # Use the output we already have
    output = """
=== Random Array Results ===
Size	Bubble Sort		Selection Sort		Insertion Sort		Heap Sort
    	Comps	Time(s)		Comps	Time(s)		Comps	Time(s)		Comps	Time(s)
1	0	1		0	1		0	1		0	1
2	1	1		1	1		1	1		6	2
3	3	1		3	1		2	1		10	2
4	6	1		6	1		3	1		20	3
5	10	2		10	2		4	1		24	4
6	15	3		15	3		5	2		34	5
7	21	3		21	3		6	2		38	7
8	28	4		28	4		7	2		52	7
9	36	5		36	4		8	2		60	9
10	45	5		45	5		9	3		70	11
11	55	7		55	6		10	2		78	12
12	66	7		66	7		11	2		92	14
13	78	9		78	9		12	3		100	16
14	91	9		91	10		13	3		110	18
15	105	10		105	11		14	2		118	19
16	120	12		120	12		15	3		132	21
17	136	13		136	13		16	4		144	22
18	153	15		153	14		17	3		158	25
19	171	15		171	16		18	3		166	27
20	190	18		190	17		19	4		180	29
21	210	19		210	18		20	4		192	31
22	231	20		231	19		21	4		204	32
23	253	21		253	20		22	5		216	34
24	276	22		276	21		23	5		228	35
25	300	23		300	22		24	5		240	37
26	325	24		325	23		25	6		252	38
27	351	25		351	24		26	6		264	40
28	378	26		378	25		27	6		276	41
29	406	27		406	26		28	7		288	43
30	435	28		435	27		29	7		300	44

=== Sorted Array Results ===
Size	Bubble Sort		Selection Sort		Insertion Sort		Heap Sort
    	Comps	Time(s)		Comps	Time(s)		Comps	Time(s)		Comps	Time(s)
1	0	1		0	0		0	1		0	1
2	1	1		1	1		1	1		6	1
3	3	1		3	1		2	1		10	2
4	6	2		6	1		3	1		20	3
5	10	2		10	2		4	1		24	5
6	15	2		15	3		5	2		34	5
7	21	3		21	3		6	1		38	6
8	28	4		28	4		7	2		52	8
9	36	5		36	5		8	2		60	10
10	45	5		45	5		9	3		70	11
11	55	6		55	6		10	2		78	12
12	66	7		66	7		11	2		92	14
13	78	8		78	8		12	3		100	16
14	91	9		91	9		13	3		110	18
15	105	10		105	11		14	3		118	19
16	120	11		120	12		15	3		132	21
17	136	13		136	12		16	3		144	22
18	153	13		153	14		17	4		158	25
19	171	16		171	15		18	4		166	27
20	190	17		190	17		19	3		180	28
21	210	18		210	18		20	4		192	30
22	231	19		231	19		21	4		204	31
23	253	20		253	20		22	5		216	33
24	276	21		276	21		23	5		228	34
25	300	22		300	22		24	5		240	36
26	325	23		325	23		25	6		252	37
27	351	24		351	24		26	6		264	39
28	378	25		378	25		27	6		276	40
29	406	26		406	26		28	7		288	42
30	435	27		435	27		29	7		300	43

=== Inverted Array Results ===
Size	Bubble Sort		Selection Sort		Insertion Sort		Heap Sort
    	Comps	Time(s)		Comps	Time(s)		Comps	Time(s)		Comps	Time(s)
1	0	0		0	1		0	1		0	1
2	1	1		1	1		1	1		6	2
3	3	1		3	1		2	1		10	2
4	6	1		6	2		3	1		20	3
5	10	2		10	2		4	1		24	4
6	15	3		15	2		5	2		34	5
7	21	3		21	3		6	2		38	7
8	28	3		28	4		7	2		52	8
9	36	4		36	5		8	2		60	9
10	45	5		45	5		9	2		70	10
11	55	6		55	6		10	2		78	12
12	66	7		66	7		11	3		92	14
13	78	8		78	8		12	3		100	16
14	91	9		91	9		13	3		110	17
15	105	10		105	10		14	2		118	19
16	120	12		120	11		15	3		132	20
17	136	12		136	13		16	4		144	23
18	153	14		153	14		17	3		158	25
19	171	15		171	15		18	3		166	26
20	190	17		190	17		19	3		180	29
21	210	18		210	18		20	4		192	30
22	231	19		231	19		21	4		204	31
23	253	20		253	20		22	5		216	33
24	276	21		276	21		23	5		228	34
25	300	22		300	22		24	5		240	36
26	325	23		325	23		25	6		252	37
27	351	24		351	24		26	6		264	39
28	378	25		378	25		27	6		276	40
29	406	26		406	26		28	7		288	42
30	435	27		435	27		29	7		300	43"""
    
    print("Parsing output...")
    dfs = parse_output(output)
    
    print("Creating Excel files...")
    create_excel_files(dfs)
    
    print("Done! Check sorting_comparisons.xlsx and sorting_runtimes.xlsx")

if __name__ == "__main__":
    main()
