import os
import re
import shutil
import requests

REPO_ROOT = os.getcwd()

# Priority used when a problem has multiple LeetCode topics.
# The first matching topic becomes the main folder.
TOPIC_PRIORITY = [
    "Array",
    "Hash Table",
    "Stack",
    "Queue",
    "Linked List",
    "Tree",
    "Binary Tree",
    "Binary Search Tree",
    "Heap (Priority Queue)",
    "Graph",
    "Depth-First Search",
    "Breadth-First Search",
    "Backtracking",
    "Dynamic Programming",
    "Greedy",
    "Trie",
    "Binary Search",
    "Two Pointers",
    "Sliding Window",
    "String",
    "Bit Manipulation",
    "Math",
    "Sorting",
    "Matrix",
    "Simulation",
    "Recursion",
]


def get_problem_slug(folder_name):
    """
    Convert a LeetHub folder name into a LeetCode slug.

    Example:
    20-valid-parentheses
    ->
    valid-parentheses
    """

    match = re.match(r"^\d+-(.+)$", folder_name)

    if match:
        return match.group(1)

    return None


def get_leetcode_tags(slug):
    """
    Get the topic tags of a LeetCode problem.
    """

    url = "https://leetcode.com/graphql"

    query = """
    query questionData($titleSlug: String!) {
        question(titleSlug: $titleSlug) {
            title
            topicTags {
                name
            }
        }
    }
    """

    variables = {
        "titleSlug": slug
    }

    try:
        response = requests.post(
            url,
            json={
                "query": query,
                "variables": variables
            },
            headers={
                "Content-Type": "application/json",
                "User-Agent": "Mozilla/5.0"
            },
            timeout=20
        )

        response.raise_for_status()

        data = response.json()

        question = data.get("data", {}).get("question")

        if not question:
            print(f"Could not find LeetCode problem: {slug}")
            return []

        tags = [
            tag["name"]
            for tag in question.get("topicTags", [])
        ]

        print(f"Tags: {tags}")

        return tags

    except Exception as error:
        print(f"Error fetching tags for {slug}: {error}")
        return []


def choose_topic(tags):
    """
    Choose one primary topic from the LeetCode tags.
    """

    for topic in TOPIC_PRIORITY:
        if topic in tags:
            return topic

    return "Other"


def normalize_folder_name(topic):
    """
    Convert LeetCode topic names into clean folder names.
    """

    replacements = {
        "Array": "Arrays",
        "Hash Table": "Hash-Table",
        "Stack": "Stack",
        "Queue": "Queue",
        "Linked List": "Linked-List",
        "Tree": "Trees",
        "Binary Tree": "Binary-Tree",
        "Binary Search Tree": "Binary-Search-Tree",
        "Heap (Priority Queue)": "Heap",
        "Graph": "Graphs",
        "Depth-First Search": "DFS",
        "Breadth-First Search": "BFS",
        "Backtracking": "Backtracking",
        "Dynamic Programming": "Dynamic-Programming",
        "Greedy": "Greedy",
        "Trie": "Trie",
        "Binary Search": "Binary-Search",
        "Two Pointers": "Two-Pointers",
        "Sliding Window": "Sliding-Window",
        "String": "Strings",
        "Bit Manipulation": "Bit-Manipulation",
        "Math": "Math",
        "Sorting": "Sorting",
        "Matrix": "Matrix",
        "Simulation": "Simulation",
        "Recursion": "Recursion",
        "Other": "Other",
    }

    return replacements.get(
        topic,
        topic.replace(" ", "-")
    )


def should_ignore(folder):
    """
    Folders that should not be processed.
    """

    ignored = {
        ".git",
        ".github",
        "scripts",
        "README.md",
        "stats.json",
    }

    return folder in ignored


def organize():
    """
    Find LeetHub problem folders in the repository root
    and move them into topic folders.
    """

    print("========================================")
    print("   LeetCode Topic Organizer")
    print("========================================")

    entries = os.listdir(REPO_ROOT)

    problem_folders = []

    # Find LeetHub-created problem folders.
    for entry in entries:

        full_path = os.path.join(
            REPO_ROOT,
            entry
        )

        if not os.path.isdir(full_path):
            continue

        if should_ignore(entry):
            continue

        if re.match(r"^\d+-", entry):
            problem_folders.append(entry)

    print(
        f"Found {len(problem_folders)} "
        f"problem folders."
    )

    # Process every problem.
    for folder in problem_folders:

        print("\n----------------------------------------")
        print(f"Processing: {folder}")

        slug = get_problem_slug(folder)

        if not slug:
            print("Could not determine LeetCode slug.")
            continue

        # Get LeetCode tags.
        tags = get_leetcode_tags(slug)

        if not tags:
            print("No tags found. Skipping.")
            continue

        # Choose primary topic.
        primary_topic = choose_topic(tags)

        # Convert topic to folder name.
        topic_folder = normalize_folder_name(
            primary_topic
        )

        # Create topic folder.
        destination_dir = os.path.join(
            REPO_ROOT,
            topic_folder
        )

        os.makedirs(
            destination_dir,
            exist_ok=True
        )

        # Current problem location.
        source = os.path.join(
            REPO_ROOT,
            folder
        )

        # New problem location.
        destination = os.path.join(
            destination_dir,
            folder
        )

        # Don't move if it already exists.
        if os.path.exists(destination):

            print(
                f"Already organized: "
                f"{topic_folder}/{folder}"
            )

            continue

        # Move the problem.
        shutil.move(
            source,
            destination
        )

        print(
            f"Moved → "
            f"{topic_folder}/{folder}"
        )

    print("\n========================================")
    print("Organization complete.")
    print("========================================")


if __name__ == "__main__":
    organize()